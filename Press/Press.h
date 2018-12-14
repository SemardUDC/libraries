#ifndef Press_h
#define Press_h

#include <Arduino.h>
#include "PCF8591.h"
class Press
{

  private:
    PCF8591 *pcf;
    uint8_t pin;

    void (*callBackFunction)(uint16_t);
    bool check_CallBackFunction();

    uint16_t analog_v;
    uint16_t mpa;
    uint16_t kpa;
    uint16_t psi;

    inline uint16_t getAnalog_v()
    {
        return this->analog_v;
    };

  public:
    Press(uint8_t _pin, void (*_callBackFunction)(uint16_t) = 0);
    Press(uint8_t _pin, PCF8591 &_pcf, void (*_callBackFunction)(uint16_t) = 0);

    void begin();
    void handle();

    virtual ~Press();

    inline void setPing(uint8_t _pin)
    {
        this->pin = _pin;
    };

    inline uint16_t getMpa()
    {
        return this->mpa;
    };

    inline uint16_t getKpa()
    {
        return this->kpa;
    };

    inline uint16_t getPsi()
    {
        return this->psi;
    };
};

#endif