#ifndef Press_h
#define Press_h

#include <Arduino.h>

class Press
{

  private:
    uint8_t pin;

    void (*callBackFunction)(void);
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
    Press(uint8_t _pin, uint16_t _analog_v, uint16_t _mpa,
          uint16_t _kpa, uint16_t _psi,
          void (*_callBackFunction)(void) = 0);

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