#include <SoftwareSerial.h>
SoftwareSerial Serial1(2, 3);

int counter;

void setup() {
  Serial.begin(115200);
  Serial1.begin(57600);

  delay(2000);
  LoRaConfig();
  Serial.println("------------------------------");
  Serial.println("------------------------------");
  delay(2000);
}

void loop() {
  counter++;
  LoRaSendAndReceive(String(counter));
  delay(30000);
}

void LoRaSendAndReceive(String data)
{
  Serial.println("");
  Serial.print("Sending: ");
  Serial.println(data);


  Serial1.write("mac tx uncnf 1 ");
  Serial1.print(data);
  Serial1.write("\r\n");

  delay(1000);
  while (Serial1.available()) Serial.write(Serial1.read());
  delay(5000);
  while (Serial1.available()) Serial.write(Serial1.read());
}

void LoRaConfig()
{
  Serial.print("Reset:\t\t");                                                                                //Device reset
  Serial1.write("sys reset\r\n");
  delay(1000);
  while (Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink(500);

  //Receive device model
  Serial.print("Device:\t\t");
  Serial1.write("sys get ver\r\n");
  delay(50);
  while (Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink(500);

  Serial.print("EUI:\t\t");                                                                                  //
  Serial1.write("sys get hweui\r\n");
  delay(50);
  while (Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink(500);

  Serial.print("addr:\t\t");                                                                                 //Set device address for your device!!!!!!!!!!!
  Serial1.write("mac set devaddr 020155A1\r\n");
  delay(50);
  while (Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink(500);

  Serial.print("nwkskey:\t");                                                                              //Set NwkSkey key for your device!!!!!!!!!!!
  Serial1.write("mac set nwkskey 2B7E151628AED2A6ABF7158809CF4F3C\r\n");
  delay(50);
  while (Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink(500);

  Serial.print("appskey:\t");
  Serial1.write("mac set appskey 2B7E151628AED2A6ABF7158809CF4F3C\r\n");                                  //Set AppSkey for your device!!!!!!!!!!
  delay(50);
  while (Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink(500);

  Serial.print("adr:\t\t");
  Serial1.write("mac set adr on\r\n");
  delay(50);
  while (Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink(500);

  //  Serial.print("data rate: ");
  //  Serial1.write("mac get dr\r\n");
  //  delay(50);
  //  while (Serial1.available()) Serial.write(Serial1.read());
  //  LoRaBlink(500);
  //
  //  Serial.print("ch: ");
  //  Serial1.write("mac get ch\r\n");
  //  delay(50);
  //  while (Serial1.available()) Serial.write(Serial1.read());
  //  LoRaBlink(500);
  //
  //  Serial.print("band: ");
  //  Serial1.write("mac get band\r\n");
  //  delay(50);
  //  while (Serial1.available()) Serial.write(Serial1.read());
  //  LoRaBlink(500);

  //  Serial.print("rx delay1: ");
  //  Serial1.write("mac get rxdelay1\r\n");
  //  delay(50);
  //  while (Serial1.available()) Serial.write(Serial1.read());
  //  LoRaBlink(500);
  //
  //  Serial.print("rx delay2: ");
  //  Serial1.write("mac get rxdelay2\r\n");
  //  delay(50);
  //  while (Serial1.available()) Serial.write(Serial1.read());
  //  LoRaBlink(500);

  Serial.print("Pwr:\t\t");
  Serial1.write("mac set pwridx 10\r\n");
  delay(50);
  while (Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink(500);

  Serial.print("Saved\t\t");
  Serial1.write("mac save\r\n");
  delay(1000);
  while (Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink(500);

  Serial.print("Join:\t\t");
  Serial1.write("mac join abp\r\n");
  delay(500);
  while (Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink(500);

  //  Serial.print("status: ");
  //  Serial1.write("mac get status\r\n");
  //  delay(50);
  //  while (Serial1.available()) Serial.write(Serial1.read());
  //  LoRaBlink(500);
}

void LoRaBlink(int timeOn) {
  Serial1.write("sys set pindig GPIO5 1\r\n");
  delay(timeOn);
  while (Serial1.available()) Serial1.read();

  Serial1.write("sys set pindig GPIO5 0\r\n");
  delay(50);
  while (Serial1.available()) Serial1.read();
}
