#ifndef ELECTROVALVULA_H

#define ELECTROVALVULA_H

#include "PCF8574.h"
#include <Arduino.h>

class Electrovalvula
{
private:
  uint8_t _estado;
  uint8_t _pin;
  PCF8574& _pcf;

public:
  const static uint8_t DESACTIVADO = 0;
  const static uint8_t ACTIVADO = 1;

  Electrovalvula(uint8_t pin, PCF8574& pcf, uint8_t estado = 0);
  ~Electrovalvula();

  void abrir();
  void cerrar();
  
  void abrir(void (*callback)(uint8_t state));  
  void cerrar(void (*callback)(uint8_t state));

  uint8_t getEstado();
  void setEstado(uint8_t estado);

  inline uint8_t getPin() { return _pin; }
  inline void setPin(uint8_t pin) { _pin = pin; }

  inline PCF8574 getPCF() { return _pcf; }
  inline void setPCF(PCF8574 pcf) { _pcf = pcf; }
};

#endif