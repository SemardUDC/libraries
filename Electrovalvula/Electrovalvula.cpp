#include "Electrovalvula.h"

Electrovalvula::Electrovalvula(uint8_t _pin, PCF8574& _pcf, uint8_t _estado)
    : pin(_pin), estado(_estado), pcf(_pcf) {}

Electrovalvula::~Electrovalvula() {}

void Electrovalvula::abrir()
{
    this->pcf.write(this->pin, HIGH);
    this->estado = ACTIVADO;
}

void Electrovalvula::cerrar()
{
    this->pcf.write(this->pin, LOW);
    this->estado = DESACTIVADO;
}

void Electrovalvula::abrir(void (*_callback)(void))
{
    this->abrir();
    if (_callback != 0)
    {
        _callback();
    }
}

void Electrovalvula::cerrar(void (*_callback)(void))
{
    this->cerrar();
    if (_callback != 0)
    {
        _callback();
    }
}