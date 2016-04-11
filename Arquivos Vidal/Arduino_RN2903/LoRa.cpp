//#define modoDebug

//////////////////////////////////////////
#include "Arduino.h"
#include "LoRa.h"
#include "SoftwareSerial.h"

SoftwareSerial Serial1(3,4);

#define RN_serial    Serial1    // Rename Serial port for LoRa Module

//variaveis e funcoes declaradas no programa principal
extern void(* ForceReset) (void);   //declare reset function at address 0

//---------------------------------------------------------------------------
void WaitResponse(int timeDelay)
{
  delay(timeDelay);

  //// aqui mostra o retorno do modulo. devo ler e se nao for OK, joined, ... resetar
#ifdef modoDebug
    while(RN_serial.available()) 
      Serial.write(RN_serial.read());
    Serial.println("");
#endif

//  ForceReset();

}
//---------------------------------------------------------------------------
void LoRa::LoRaConfig()
{
  delay(2000);
#ifdef modoDebug
  Serial.print("Reset: ");                                                                                //Device reset
#endif
  RN_serial.write("sys reset\r\n");
  WaitResponse(2000);
  
#ifdef modoDebug
  Serial.print("Set DevEui: ");                                                                                  // set DEVEUI
#endif
  RN_serial.write("mac set deveui 0004A300020155A0\r\n");
  WaitResponse(1000);
  
#ifdef modoDebug
  Serial.print("Set DevADDr/NwkAddr: ");                                                              //Set device address for your device!!!!!!!!!!!
#endif
  RN_serial.write("mac set devaddr 020155A0\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Set AppSkey: ");
#endif
  RN_serial.write("mac set appskey 2B7E151628AED2A6ABF7158809CF4F3C\r\n");                                  //Set AppSkey for your device!!!!!!!!!!
  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Set NwkSkey: ");                                                                      //Set NwkSkey key for your device!!!!!!!!!!!
#endif
  RN_serial.write("mac set nwkskey 2B7E151628AED2A6ABF7158809CF4F3C\r\n");
  WaitResponse(1000);
  
#ifdef modoDebug
  Serial.print("Set ADR On: ");
#endif
  RN_serial.write("mac set adr on\r\n");
  WaitResponse(1000);
  
#ifdef modoDebug
  Serial.print("Set Pwr: ");                                                                            
#endif
  RN_serial.write("radio set pwr 20\r\n");
  WaitResponse(1000);

  // Canais off - Ex.: mac set ch status 24 off<0d0a>
#ifdef modoDebug
  Serial.println("Desabilitando canais 8 a 71");
#endif
  for (int loop=8;loop<72;loop++)            // desligo do 8 ao 71
  { 
    RN_serial.write("mac set ch status ");
    RN_serial.print(loop);
    RN_serial.write(" off\r\n");

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
  RN_serial.write("mac save\r\n");
  WaitResponse(1000);

#ifdef modoDebug
  Serial.print("Join: ");
#endif
  RN_serial.write("mac join abp\r\n");
  WaitResponse(1000);
}
//---------------------------------------------------------------------------
void LoRa::LoRaSendUncnf(int data)
{
#ifdef modoDebug
    Serial.println("");
    Serial.print("Sending: ");
    Serial.println(data);
#endif

    RN_serial.write("mac tx uncnf 1 ");
    RN_serial.print(data);
    RN_serial.write("\r\n");

    WaitResponse(1000);                             //receive ok from module

    WaitResponse(5000);                         //receive mac_tx_ok from data sent
}
//---------------------------------------------------------------------------
void LoRa::LoRaWriteGpio(int gpiopin, int value)
{
#ifdef modoDebug
    Serial.print("GPIO ");
    Serial.print(gpiopin);
    if (value==0)
        Serial.println(" apagado");
    else
        Serial.println(" aceso");
#endif

    RN_serial.write("sys set pindig GPIO");
    RN_serial.print(gpiopin);
    if (value==0)
      RN_serial.write(" 0\r\n");
    else
      RN_serial.write(" 1\r\n");

    WaitResponse(200);                             //receive ok from module
}
//---------------------------------------------------------------------------

