#ifndef PCF8574_h

#define PCF8574_h

// Specialized library when dealing with
// PCF8574 on the ESP and multiple I2C
// buses.
#include <pcf8574_esp.h>
#include <Wire.h>

class PCF8574
{
  private:
    uint8_t _sda;
    uint8_t _scl;
    uint8_t _address;
    // If multiple I2C buses are being used
    // by the ESP, it stablishes the execution
    // of Wire.begin() for every read/write
    // operation with the _sda and _scl configured.
    bool _multiple;

    PCF857x _internal_pcf;

  public:
    PCF8574(uint8_t address, uint8_t sda, uint8_t scl, bool _multiple = false);
    ~PCF8574();
    void begin();
    void write(uint8_t pin, uint8_t value);
};

#endif