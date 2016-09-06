//BIBLIOTECAS
#include <TheThingsUno.h>
TheThingsUno ttu;

#include <DHT.h>
#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#include <SoftwareSerial.h>
SoftwareSerial Serial1(2, 3);
#define debugSerial Serial
#define loraSerial Serial1

#define debugPrintLn(...) { if (debugSerial) debugSerial.println(__VA_ARGS__); }
#define debugPrint(...) { if (debugSerial) debugSerial.print(__VA_ARGS__); }

//CONSTANTES E VARIAVEIS
const byte devAddr[4] = {0x02, 0x01, 0x55, 0xB0};
const byte nwkSKey[16] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};
const byte appSKey[16] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};

byte data[6];


void setup() {
  debugSerial.begin(115200);
  loraSerial.begin(57600);
  dht.begin();
  delay(1000);

  ttu.init(loraSerial, debugSerial);
  ttu.reset();
  ttu.personalize(devAddr, nwkSKey, appSKey);
  delay(6000);

  ttu.showStatus();
  debugPrintLn("Setup complete!");
  delay(1000);
}

void loop() {
  LeSensores();
  ttu.sendBytes(data, sizeof(data), 10, true);

  for (int t = 0; t < 15 * 60; t++) {
    delay(1000);
  }
}

void LeSensores() {
  int16_t temperature = dht.readTemperature() * 10;
  data[0] = highByte(temperature);
  data[1] = lowByte(temperature);
  debugPrint("Temperatura: "); debugPrintLn(temperature / 10.0);

  int16_t humidity = dht.readHumidity() * 10;
  data[2] = highByte(humidity);
  data[3] = lowByte(humidity);
  debugPrint("Umidade: "); debugPrintLn(humidity / 10.0);

  float vout = analogRead(A0);    //Le valor pino analogico sensor de pressao
  vout = (vout * 5.0) / 1023.0;   //Converte valor 0-1023 para 0-5V
  int16_t pres = round(222 * vout + 106);        //Converte o valor para hPa
  data[4] = highByte(pres);
  data[5] = lowByte(pres);
  debugPrint("Pressao: "); debugPrintLn(pres);
}

