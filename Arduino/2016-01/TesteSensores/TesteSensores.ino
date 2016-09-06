//Libraries
#include <DHT.h>;
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <EEPROM.h>

//Constants
#define DHTPIN 3         // pino digital sensor temp e umidade
#define PRESPIN 0        // pino analogico pressostato
#define DHTTYPE DHT22    // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT sensor for normal 16mhz Arduino


//Variaveis
float umid;   //Valor umidade (%)
float temp;   //Valor temperatura (Celsius)
float pres; //Valor pressao (hPa)

volatile int f_wdt=1;
volatile int cont = 0;
volatile int addr = 0;

ISR(WDT_vect)
{
  if(f_wdt == 0)
  {
    f_wdt=1;
  }
  else
  {
    Serial.println("WDT Overrun!!!");
  }
}

void enterSleep(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);   /* EDIT: could also use SLEEP_MODE_PWR_DOWN for lowest power consumption. */
  sleep_enable();
  
  /* Now enter sleep mode. */
  sleep_mode();
  
  /* The program will continue from here after the WDT timeout*/
  sleep_disable(); /* First thing to do is disable sleep. */
  
  /* Re-enable the peripherals. */
  power_all_enable();
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Initialising...");
  delay(100); //Allow for serial print to complete.

  //Inicia DHT
  dht.begin();

  /*** Setup the WDT ***/
  
  /* Clear the reset flag. */
  MCUSR &= ~(1<<WDRF);
  
  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  /* set new watchdog timeout prescaler value */
  WDTCSR = 1<<WDP0 | 1<<WDP3; /* 8.0 seconds */
  
  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);
  
  Serial.println("Initialisation complete.");
  delay(100); //Allow for serial print to complete. 
}

void loop()
{
  if(f_wdt == 1)
  {
    cont += 1;
    if (cont >= 1){ //110*8 = 880s = 14min 40s 
      //LeSensores();
      temp = dht.readTemperature();
      temp = constrain(temp,10.0,35.5); //Temp min = 10, Temp max = 35.5
      temp = (temp - 10.0)* 10;         //Altera valor da temp para ficar entre 0 e 255
      byte tempByte = (byte)temp;       //Transforma em byte

//      EEPROM.write(addr, tempByte);  
//      
//      addr = addr + 1;
//      if (addr == EEPROM.length()) 
//        addr = 0;
              
      cont = 0;    
    }
    
    //Limpa o flag e entra em Sleep
    f_wdt = 0;
    enterSleep();
  }
}

void LeSensores(){
  umid = dht.readHumidity();        //Le valor umidade em %
  temp = dht.readTemperature();     //Le valor temperatura em Celsius

   // Check if any reads failed and exit early (to try again).
   if (isnan(umid) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
   }
  
  float vout = analogRead(A0);    //Le valor pino analogico sensor de pressao
  vout = (vout * 5.0) / 1023.0;   //Converte valor 0-1023 para 0-5V
  pres = 222 * vout + 106;        //Converte o valor para hPa
  
  PrintValues(umid, temp, pres); 
}

void PrintValues (float umidade, float temperatura, float pressao)
{
  Serial.print("Umidade: "); 
  Serial.print(umidade);
  Serial.print(" %\t");
  Serial.print("Temperatura: "); 
  Serial.print(temperatura);
  Serial.print(" *C\t ");
  Serial.print("Humidity: ");
  Serial.print(pressao);
  Serial.println(" hPa");
  delay(100);
}
