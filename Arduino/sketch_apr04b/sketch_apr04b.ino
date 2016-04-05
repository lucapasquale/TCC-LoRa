#include <SoftwareSerial.h>
SoftwareSerial Serial1(2, 3);

void setup() {
  Serial.begin(9600);
  Serial1.begin(57600);

  delay(2000);
  Serial.println("Configuring LoRa module...");
  
  Serial.print("Reset: ");                                                                                //Device reset
  Serial1.write("sys reset\r\n");
  delay(1000);
  while(Serial1.available()) Serial.write(Serial1.read());
  BlinkLed();
  
  Serial.print("Device:  ");
  Serial1.write("sys get ver\r\n");
  delay(50);
  while(Serial1.available()) Serial.write(Serial1.read());
}

void loop() {
  // put your main code here, to run repeatedly:

}

void BlinkLed(){
  Serial1.write("sys set pindig GPIO5 1\r\n");
  delay(500);
  while(Serial1.available()) Serial1.read();
  Serial1.write("sys set pindig GPIO5 0\r\n");
  delay(50);
  while(Serial1.available()) Serial1.read();
}

