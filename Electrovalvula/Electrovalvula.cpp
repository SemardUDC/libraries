#include "Electrovalvula.h"

Electrovalvula::Electrovalvula(uint8_t pin, PCF8574& pcf, uint8_t estado)
    : _pin(pin), _estado(estado), _pcf(pcf) {}

Electrovalvula::~Electrovalvula() {}

uint8_t Electrovalvula::getEstado()
{
    return _estado;
}

void Electrovalvula::setEstado(uint8_t estado)
{
    if (estado == ACTIVADO)
    {
        _estado = estado;
        abrir();
    }
    else if (estado == DESACTIVADO)
    {
        _estado = estado;
        cerrar();
    }
}

void Electrovalvula::abrir()
{
    _pcf.write(_pin, HIGH);
    _estado = ACTIVADO;
}

void Electrovalvula::cerrar()
{
    _pcf.write(_pin, LOW);
    _estado = DESACTIVADO;
}

void Electrovalvula::abrir(void (*callback)(uint8_t state))
{
    abrir();
    if (callback != 0)
    {
        callback(_estado);
    }
}

void Electrovalvula::cerrar(void (*callback)(uint8_t state))
{
    cerrar();
    if (callback != 0)
    {
        callback(_estado);
    }
}