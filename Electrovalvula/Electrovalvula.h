#ifndef ELECTROVALVULA_H

#define ELECTROVALVULA_H

#include <PCF8574.h>
#include <Arduino.h>

class Electrovalvula
{
private:
  uint8_t estado;
  uint8_t pin;
  PCF8574& pcf;

public:
  const static uint8_t DESACTIVADO = 0;
  const static uint8_t ACTIVADO = 1;

  Electrovalvula(uint8_t _pin, PCF8574& _pcf, uint8_t _estado = 0);
  ~Electrovalvula();

  void abrir();
  void cerrar();
  
  void abrir(void (*_callback)(void));  
  void cerrar(void (*_callback)(void));

  inline uint8_t getEstado() { return this->estado; }
  inline void setEstado(uint8_t _estado)
  {
    if (_estado == ACTIVADO)
    {
      this->estado = _estado;
      this->abrir();
    }
    else if(_estado == DESACTIVADO)
    {
      this->estado = _estado;
      this->cerrar();
    }
  }

  inline uint8_t getPin() { return this->pin; }
  inline void setPin(uint8_t _pin) { this->pin = _pin; }

  inline PCF8574 getPCF() { return this->pcf; }
  inline void setPCF(PCF8574 _pcf) { this->pcf = _pcf; }
};

#endif