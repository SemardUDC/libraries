#include "PCF8574.h"

PCF8574::PCF8574(uint8_t address, uint8_t sda, uint8_t scl, bool multiple)
    : _address(address),
      _sda(sda),
      _scl(scl),
      _multiple(multiple),
      _internal_pcf(address, &Wire)
{
}

PCF8574::~PCF8574() {}

void PCF8574::begin()
{
    Wire.begin(_sda, _scl);
}

void PCF8574::write(uint8_t pin, uint8_t value)
{
    if (_multiple)
        begin();

    _internal_pcf.write(pin, value);
}

uint8_t PCF8574::read(uint8_t pin)
{
    if (_multiple)
        begin();

    return _internal_pcf.read(pin);
}