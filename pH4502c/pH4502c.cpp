#include "pH4502c.h"

pH4502c::pH4502c(PCF8591 &_pcf, uint8_t _pin, void (*_callback)(float_t))
    : pcf(&_pcf), pin(_pin), callback(_callback)
{
    // Without the delay, the class will
    // not work.
    delay(200);
}

pH4502c::pH4502c(uint8_t _pin, void (*_callback)(float_t))
    : pcf(nullptr), pin(_pin), callback(_callback)
{
    // Just for caution.
    delay(200);
}

pH4502c::~pH4502c()
{
}

float_t pH4502c::handle()
{
    int buf[10], temp;
    unsigned long int avgValue;
    for (int i = 0; i < 10; i++)
    {
        if (!pcf)
        {
            buf[i] = analogRead(pin);
        }
        else
        {
            buf[i] = pcf->lecturaAnalogica(pin);
        }        
        delay(100);
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            if (buf[i] > buf[j])
            {
                temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }
    avgValue = 0;
    for (int i = 2; i < 8; i++)
        avgValue += buf[i];
    this->pHVol = (float)avgValue * 3.3 / 254 / 6;
    this->pHVal = 2.4 * this->pHVol + 1;
    this->callback(this->pHVal);
    return this->pHVal;
}
