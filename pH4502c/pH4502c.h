#ifndef PH4502C_H
#define PH4502C_H

#include <Arduino.h>
#include "PCF8591.h"
class pH4502c {
  private:
    uint8_t medida;
    float_t pHVol;
    float_t pHVal;
    PCF8591& pcf;
    void(*callback)(float_t);
    uint8_t pin;

  public:
    //Retorna valores bi-decimales de entre 0-14
    //De acuerdo a la escala de pH
    float_t lecturaAnalogica();
    pH4502c(PCF8591 _pcf, uint8_t _pin, void(*_callback)(float_t) );


};
#endif
