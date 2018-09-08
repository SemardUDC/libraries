#ifndef Press_h
#define Press_h

#include <Arduino.h>

class PressureS
{

  private:
    uint8_t pin;
    uint16_t analog_v;
    uint16_t mpa;
    uint16_t kpa;
    uint16_t psi;

    void (*callBackFunction)(void)
    {
        if (callBackFunction)
        {
            (*callBackFunction)();
        }
    }

    inline void getAnalog_v()
    {
        return this->analog_v;
    }

  public:
    Press(uint8_t _pin, void (*callBackFunction)(void) = 0, uint16_t _analog_v, uint16_t _mpa,
          uint16_t _kpa, uint16_t _psi);

    void begin();
    void handle();

    virtual dPress;

    inline void setPing(uint8_t _pin)
    {
        this->pin = _pin;
    }

    inline void getMpa()
    {
        return this->mpa;
    }

    inline void getKpa()
    {
        return this->kpa;
    }

    inline void getPsi()
    {
        return this->psi;
    }
};

#endif