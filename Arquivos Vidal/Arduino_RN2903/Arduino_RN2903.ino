//////////////////////////////////////////////////
//  Programa : Arduino + LoRa
//
//  Vidal - 30/03/2016
//////////////////////////////////////////////////
/// Definicao da placa. IMPORTANTE
//
//#define _Leonardo    //comentar para uno e outros
//
//#define modoDebug
//////////////////////////////////////////////////

#ifdef _Leonardo
  // nada a fazer
#else
 #include <SoftwareSerial.h>
#endif

//////////////////////////////////////////////////
#define RN_serial    Serial1  

#include "LoRa.h"       // definicoes do modulo lora RN2903

LoRa LoRa_Lib;

//////////////////////////////////////////////////////////////////////
// Pinos
int POT = A0;         // potenciometro
int LM35 = A1;        // temperatura
int ledVM = 11;      // led Vermelho
int rst = 7;      // reset RN em 0

// variaveis
int adPOT = 0;  // variable to store the value coming from the sensor
int adLM35 = 0;
float temperatura = 0;
float tensaoPOT = 0;
int passagem = 0;
int K_espera = 10;
int envio=0;
int tempsim;

// variaveis "globais"
// para usar no modulo lora.cpp redefinir como external
void(* ForceReset) (void) = 0;    // funcao reset
///////////////////////////////////////////////////////////////////////
void setup() 
{
  pinMode(rst, OUTPUT);  
  digitalWrite(rst, HIGH); 
   
  pinMode(ledVM, OUTPUT);  
  digitalWrite(ledVM, LOW);  

#ifdef _Leonardo
  //Inicializa serial monitor com PC pelo usb
  #ifdef modoDebug
    Serial.begin(57600);
    while (!Serial);      // se em modo debug espero o monitor serial

    Serial.println("Leonardo - Monitor Serial USB");
    Serial.println("Pinos D0/Rx e D1/Tx usados para o modulo RN2903");     
    Serial.println("");
  #endif
#else
     //// Serial externo usar a biblioteca SoftwareSerial.h e usar outros pinos D2/D3
    Serial.begin(9600);
    Serial.print("a");
#endif

  //================================= LoRa 
#ifdef _Leonardo
  RN_serial.begin(57600);
#else
    ////// programar o serial por software
    
#endif

  digitalWrite(rst, LOW); 
#ifdef modoDebug
  Serial.println("");
  Serial.print("Reseting");
  Serial.print("..");  delay(100);
  Serial.print("..");  delay(100);
  Serial.print("..");  delay(100);
  Serial.print("..");  delay(100);
  Serial.print("..");  delay(100);
#endif
  digitalWrite(rst, HIGH); 

#ifdef modoDebug
  Serial.println("");
  Serial.println("Aguarde.");
  Serial.println("");
#endif  
  delay(5000);

#ifdef modoDebug
  while(RN_serial.available()) 
    Serial.write(RN_serial.read());
  
  Serial.println("");

  Serial.println("");
  Serial.println("==========================================");
  Serial.println("=====  Configurando o modulo RN2903  =====");
  Serial.println("==========================================");
  Serial.println("");
#endif

  LoRa_Lib.LoRaConfig();                                        // Run config

//  digitalWrite(ledVM, HIGH);  
  LoRa_Lib.LoRaWriteGpio(5,1);
  delay(200);

//  digitalWrite(ledVM, LOW); 
  LoRa_Lib.LoRaWriteGpio(5,0);
  delay(200);
  
//  digitalWrite(ledVM, HIGH);  
  LoRa_Lib.LoRaWriteGpio(5,1);
  delay(200);
  
//  digitalWrite(ledVM, LOW); 
  LoRa_Lib.LoRaWriteGpio(5,0);
  delay(200);
}
///////////////////////////////////////////////////////////////////////
void loop() 
{
//    // le o valor do trimpot
//    adPOT = analogRead(POT);    
//    tensaoPOT = adPOT * (5.0/1023);
//    
//    // le o valor do LM35
//    adLM35 = analogRead(LM35);    
//    temperatura = adLM35 * (500.0/1023);
//
//    Serial.print("Tensao no POT:  ");
//    Serial.print(tensaoPOT);
//    Serial.print(" V    ");
// 
//    Serial.print("Temperatura:   ");
//    Serial.print(temperatura,1);
//    Serial.print(" oC ");

#ifdef modoDebug  
    Serial.println("   ");
#endif

//    digitalWrite(ledVM, HIGH);  
    LoRa_Lib.LoRaWriteGpio(5,1);
    delay(50);

//    digitalWrite(ledVM, LOW);  
    LoRa_Lib.LoRaWriteGpio(5,0);
    delay(950);

    passagem++;
    if (passagem>K_espera)
    {
      passagem=0;
      envio++;    
      if (envio>20)
        envio=1;

      switch(envio)
      {
        case  1: {tempsim = 168; break; }
        case  2: {tempsim = 172; break; }
        case  3: {tempsim = 189; break; }
        case  4: {tempsim = 198; break; }
        case  5: {tempsim = 205; break; }
        case  6: {tempsim = 212; break; }
        case  7: {tempsim = 228; break; }
        case  8: {tempsim = 234; break; }
        case  9: {tempsim = 219; break; }
        case 10: {tempsim = 198; break; }
        case 11: {tempsim = 176; break; }
        case 12: {tempsim = 172; break; }
        case 13: {tempsim = 189; break; }
        case 14: {tempsim = 190; break; }
        case 15: {tempsim = 195; break; }
        case 16: {tempsim = 212; break; }
        case 17: {tempsim = 208; break; }
        case 18: {tempsim = 200; break; }
        case 19: {tempsim = 188; break; }
        case 20: {tempsim = 176; break; }
      }

      
      LoRa_Lib.LoRaSendUncnf(tempsim);                       // Make a new ping 

//      digitalWrite(ledVM, HIGH);  
      LoRa_Lib.LoRaWriteGpio(5,1);
      delay(50);
      
//      digitalWrite(ledVM, LOW);  
      LoRa_Lib.LoRaWriteGpio(5,0);
      delay(50);
    }
}


