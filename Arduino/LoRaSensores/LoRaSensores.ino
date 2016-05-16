//-------------Constantes-----------------------------------------------
#define DHTPIN 5         // pino digital sensor temp e umidade
#define PRESPIN 0        // pino analogico pressostato
#define DHTTYPE DHT22    // DHT 22  (AM2302)
#define delayMessage 10000

//-----------Bibliotecas e Definicoes-----------------------------
#define modoDebug;
#define modoTimer;

#include <TinyGPS++.h>
TinyGPSPlus gps;
#include <DHT.h>
DHT dht(DHTPIN, DHTTYPE);
#include <SoftwareSerial.h>
SoftwareSerial Serial1(2, 3);
SoftwareSerial SerialGPS(9, 10);


#ifdef modoTimer
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#endif

//---------------Variaveis--------------------------------------------
long umid;   //Valor umidade (%)
long temp;   //Valor temperatura (Celsius)
long pres;   //Valor pressao (hPa)
long GPSlat;
long GPSlng;

long sensores[5];
//1: Temperatura
//2: Umidade
//3: Pressao
//4: Longitude
//5: Latitude

volatile int f_wdt = 1;
volatile int cont = 110;

//--------------Arduino------------------------------------------
void setup() {
#ifdef modoDebug
  Serial.begin(115200);
#endif

  dht.begin();
  Serial1.begin(57600);
  SerialGPS.begin(9600);
  LoRaConfig();

#ifdef modoTimer
  MCUSR &= ~(1 << WDRF);
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  WDTCSR = 1 << WDP0 | 1 << WDP3;
  WDTCSR |= _BV(WDIE);
#endif
}

void loop() {
#ifdef modoTimer
  if (f_wdt == 1)
  {
    cont += 1;
    if (cont >= 110) { //110*8 = 880s = 14min 40s
      LeSensores();
      LoRaSendUncnf(temp, 10);
      LoRaSendUncnf(umid, 20);
      LoRaSendUncnf(pres, 30);
      cont = 0;
    }
    //Limpa o flag e entra em Sleep
    f_wdt = 0;
    enterSleep();
  }
#else

#ifdef modoDebug
  Serial.print(F("Location: "));
  Serial.print(gps.location.lat(), 6);
  Serial.print(F(","));
  Serial.println(gps.location.lng(), 6);
#endif
  LoRaSendUncnf(GPSlat);
  LoRaSendUncnf(GPSlng);
  delay(delayMessage);
#endif
}

//------------------Watchdog Timer------------------------------------
#ifdef modoTimer
ISR(WDT_vect)
{
  if (f_wdt == 0)
    f_wdt = 1;
  else
  {
#ifdef modoDebug
    Serial.println("WDT Overrun!!!");
#endif
  }
}

void enterSleep(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  power_all_enable();
}
#endif

//----------------Sensores-------------------------------------------
void LeSensores() {
  umid = round(10 * dht.readHumidity());      //Le valor umidade em %
  temp = round(10 * dht.readTemperature());     //Le valor temperatura em Celsius

  float vout = analogRead(A0);    //Le valor pino analogico sensor de pressao
  vout = (vout * 5.0) / 1023.0;   //Converte valor 0-1023 para 0-5V
  pres = round(222 * vout + 106);        //Converte o valor para hPa

  sensores[1] = temp;
  sensores[2] = umid;
  sensores[3] = pres;

#ifdef ModoDebug
  if (isnan(umid) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Umidade: ");
  Serial.print(umid);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" *C\t ");
  Serial.print("Humidity: ");
  Serial.print(pres);
  Serial.println(" hPa");
  delay(100);
#endif
}

//---------------------LoRa--------------------------------
void LoRaSendUncnf(long data, int port)
{
  LoRaWriteGpio(5, 1);
  delay(50);

  LoRaWriteGpio(5, 0);
  delay(950);

#ifdef modoDebug
  Serial.println("");
  Serial.print("Sending: ");
  Serial.print(data);
//  for (int j = 0; j < sizeof(sensores) / sizeof(long); j++) {
//      Serial.print(data[j]);
//      Serial.print(" ");
//  }
;
#endif

  Serial1.write("mac tx uncnf ");
  Serial1.print(port);
  Serial1.write(" ");
  Serial1.print(data);

//  for (int i = 0; i < sizeof(data) / sizeof(long); i++) {
//    Serial1.write(" ");
//    Serial1.print(data[i]);
//  }

  Serial1.write("\r\n");

  WaitResponse(1000);                             //receive ok from module

  WaitResponse(5000);                         //receive mac_tx_ok from data sent

  LoRaWriteGpio(5, 1);
  delay(50);

  LoRaWriteGpio(5, 0);
  delay(950);

}

void WaitResponse(int timeDelay)
{
  delay(timeDelay);

  //// aqui mostra o retorno do modulo. devo ler e se nao for OK, joined, ... resetar
#ifdef modoDebug
  while (Serial1.available()) Serial.write(Serial1.read());
  Serial.println("");
#endif
}

void LoRaConfig()
{
  delay(2000);
#ifdef modoDebug
  Serial.print("Reset: ");
#endif
  Serial1.write("sys reset\r\n");
  WaitResponse(2000);

  #ifdef modoDebug
    Serial.print("Set DevEui: ");
  #endif
    Serial1.write("mac set deveui 0004A30B001A674B\r\n");
    WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Set DevADDr/NwkAddr: ");
#endif
  Serial1.write("mac set devaddr 020155B0\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Set AppSkey: ");
#endif
  Serial1.write("mac set appskey 2B7E151628AED2A6ABF7158809CF4F3C\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Set NwkSkey: ");
#endif
  Serial1.write("mac set nwkskey 2B7E151628AED2A6ABF7158809CF4F3C\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Set ADR On: ");
#endif
  Serial1.write("mac set adr on\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Set Pwr: ");
#endif
  Serial1.write("radio set pwr 20\r\n");
  WaitResponse(1000);

  // Canais off - Ex.: mac set ch status 24 off<0d0a>
#ifdef modoDebug
  Serial.println("Desabilitando canais 8 a 71");
#endif
  for (int i = 8; i < 72; i++)      // desligo do 8 ao 71
  {
    Serial1.write("mac set ch status ");
    Serial1.print(i);
    Serial1.write(" off\r\n");

    WaitResponse(200);

#ifdef modoDebug
    Serial.print("Canal ");
    Serial.print(i);
    Serial.println(" desativado.");
#endif
  }

#ifdef modoDebug
  Serial.print("SAVE: ");
#endif
  Serial1.write("mac save\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Join: ");
#endif
  Serial1.write("mac join abp\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.println("------------------------------");
  Serial.println("-------LoRa Configurado-------");
  Serial.println("------------------------------");
  Serial.println("");
#endif
  delay(2000);
}

void LoRaWriteGpio(int gpiopin, int state)
{
#ifdef modoDebug
  Serial.print("GPIO ");
  Serial.print(gpiopin);
  if (state == 0)
    Serial.println(" desligado");
  else
    Serial.println(" ligado");
#endif

  Serial1.write("sys set pindig GPIO");
  Serial1.print(gpiopin);
  if (state == 0)
    Serial1.write(" 0\r\n");
  else
    Serial1.write(" 1\r\n");

  WaitResponse(200);                             //receive ok from module
}
