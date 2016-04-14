#include <SoftwareSerial.h>
SoftwareSerial Serial1(2, 3);

#define modoDebug;
#define delayMessage 10000

int counter;

void setup() {
#ifdef modoDebug
  Serial.begin(115200);
#endif

  Serial1.begin(57600);
  LoRaConfig();
}

void loop() {
  counter++;
  LoRaSendUncnf(counter);
  delay(delayMessage);
}

void LoRaSendUncnf(int data)
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

  Serial.write("mac tx uncnf 1 ");
  Serial.print(data);
  Serial.write("\r\n");

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

  //#ifdef modoDebug
  //  Serial.print("Set DevEui: ");
  //#endif
  //  Serial1.write("mac set deveui 0004A300020155A0\r\n");
  //  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Set DevADDr/NwkAddr: ");
#endif
  Serial1.write("mac set devaddr 020155A0\r\n");
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
  for (int loop = 8; loop < 72; loop++)      // desligo do 8 ao 71
  {
    Serial1.write("mac set ch status ");
    Serial1.print(loop);
    Serial1.write(" off\r\n");

    WaitResponse(200);

#ifdef modoDebug
    Serial.print("Canal ");
    Serial.print(loop);
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

  Serial.write("sys set pindig GPIO");
  Serial.print(gpiopin);
  if (state == 0)
    Serial.write(" 0\r\n");
  else
    Serial.write(" 1\r\n");

  WaitResponse(200);                             //receive ok from module
}
