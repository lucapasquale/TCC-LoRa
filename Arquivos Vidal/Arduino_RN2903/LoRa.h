#ifndef LoRa_h
#define LoRa_h

#include <avr/pgmspace.h>

#include <Arduino.h>

class LoRa
{
  private:

  
  public:
    void LoRaConfig();
    void LoRaSendUncnf(int data);
    void LoRaWriteGpio(int gpiopin, int value);
    
};
#endif
 
