//----------------------Constantes--------------------------------------------
#define DHTPIN 5         // pino digital sensor temp e umidade
#define PRESPIN 0        // pino analogico pressostato
#define DHTTYPE DHT22    // DHT 22  (AM2302)
#define delayMessage 10000

//-----------------------Bibliotecas e Definicoes-----------------------------
#define modoDebug

#include <TinyGPS++.h>
TinyGPSPlus gps;
#include <DHT.h>
DHT dht(DHTPIN, DHTTYPE);
#include <SoftwareSerial.h>
SoftwareSerial SerialLoRa(2, 3);
SoftwareSerial SerialGPS(9, 10);

//-----------------------Variaveis-------------------------------------------
String dadosEnviar;
unsigned long dadosLong[3]; //0 = temp, 1 = umid, 2 = pres

//-----------------------Arduino----------------------------------------------
void setup() {
#ifdef modoDebug
  Serial.begin(115200);
#endif

  SerialLoRa.begin(57600);
  LoRaConfig();
}

void loop() {
  LeSensores();
  LoRaSendUncnf(dadosEnviar);

  for (int t = 0; t < 6 * 15; t++) {
    delay(delayMessage);
  }
}

String transformHex(int num, int precision) {
  char tmp[16];
  char format[128];

  sprintf(format, "%%.%dX", precision);

  sprintf(tmp, format, num);
  return tmp;
}

//-----------------------Sesnsores------------------------------------------
void LeSensores() {
  dadosLong[0] = round(10 * dht.readTemperature());   //Le valor temperatura em Celsius
  dadosLong[1] = round(10 * dht.readHumidity());      //Le valor umidade em %

  float vout = analogRead(A0);    //Le valor pino analogico sensor de pressao
  vout = (vout * 5.0) / 1023.0;   //Converte valor 0-1023 para 0-5V
  dadosLong[2] = round(222 * vout + 106);        //Converte o valor para hPa

  dadosEnviar = "";
  for (int i = 0; i < (sizeof(dadosLong) / sizeof(unsigned long)); i++) {
    dadosEnviar += transformHex(dadosLong[i], 4);
  }
}

//-----------------------LoRa---------------------------------------------
void LoRaSendUncnf(String data)
{
  LoRaWriteGpio(5, 1);
  delay(50);

  LoRaWriteGpio(5, 0);
  delay(950);

#ifdef modoDebug
  Serial.println("");
  Serial.print("Sending: ");
  Serial.println(data);
#endif

  SerialLoRa.write("mac tx uncnf 1 ");
  SerialLoRa.print(data);
  SerialLoRa.write("\r\n");

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

#ifdef modoDebug
  while (SerialLoRa.available()) Serial.write(SerialLoRa.read());
#endif
}

void LoRaConfig()
{
  delay(2000);
#ifdef modoDebug
  Serial.print("Reset: ");
#endif
  SerialLoRa.write("sys reset\r\n");
  WaitResponse(2000);

#ifdef modoDebug
  Serial.print("Set DevEui: ");
#endif
  SerialLoRa.write("mac set deveui 0004A30B001A674B\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Set DevADDr/NwkAddr: ");
#endif
  SerialLoRa.write("mac set devaddr 020155B0\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Set AppSkey: ");
#endif
  SerialLoRa.write("mac set appskey 2B7E151628AED2A6ABF7158809CF4F3C\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Set NwkSkey: ");
#endif
  SerialLoRa.write("mac set nwkskey 2B7E151628AED2A6ABF7158809CF4F3C\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Set ADR On: ");
#endif
  SerialLoRa.write("mac set adr on\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Set Pwr: ");
#endif
  SerialLoRa.write("radio set pwr 20\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.println("Desabilitando canais 8 a 71");
#endif
  for (int i = 8; i < 72; i++)      // desligo do 8 ao 71
  {
    SerialLoRa.write("mac set ch status ");
    SerialLoRa.print(i);
    SerialLoRa.write(" off\r\n");

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
  SerialLoRa.write("mac save\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Join: ");
#endif
  SerialLoRa.write("mac join abp\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.println("------------------------------");
  Serial.println("-------LoRa Configurado-------");
  Serial.println("------------------------------");
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

  SerialLoRa.write("sys set pindig GPIO");
  SerialLoRa.print(gpiopin);
  if (state == 0)
    SerialLoRa.write(" 0\r\n");
  else
    SerialLoRa.write(" 1\r\n");

  WaitResponse(200);                             //receive ok from module
}
