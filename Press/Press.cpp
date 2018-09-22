#include <Press.h>

#ifdef PRESS_DEBUG
#define PRESS_DEBUG_PRINT(String) (Serial.println(String))
#endif

#ifndef PRESS_DEBUG
#define PRESS_DEBUG_PRINT(String)

#endif

Press::Press(uint8_t _pin, uint16_t _analog_v, uint16_t _mpa,
             uint16_t _kpa, uint16_t _psi, 
             void (*_callBackFunction)(void))
{
    this->pin = _pin;
    this->callBackFunction = _callBackFunction;
    this->analog_v = _analog_v;
    this->mpa = _mpa;
    this->kpa = _kpa;
    this->psi = _psi;
}

Press::~Press()
{
    PRESS_DEBUG_PRINT("Deleting Press Object");
}

void Press::begin()
{
    pinMode(pin, INPUT);
    PRESS_DEBUG_PRINT("Initializing Pin ");
    check_CallBackFunction(); //VOID
}

void Press::handle()
{
    analog_v = analogRead(this->pin);
    float press_MPa = (analog_v / 1024 - 0.1) / 0.75;
    float press_kPa = press_MPa * 1000;
    float press_psi = press_kPa * 0.14503773773020923; /*
    PRESS_DEBUG_PRINT("The pressure is "+press_MPa+"MPa.");
    PRESS_DEBUG_PRINT("The pressure is "+press_kPa+"kPa.");
    PRESS_DEBUG_PRINT("The pressure is "+press_psi+"psi."); */

    this->mpa = press_MPa;
    this->kpa = press_kPa;
    this->psi = press_psi;

    callBackFunction(); //CallBack invocation
}

bool Press::check_CallBackFunction()

{
    if (!this->callBackFunction)
    {
        PRESS_DEBUG_PRINT("Press does not have a CallBack");
        return false;
    }
    PRESS_DEBUG_PRINT("CallBack exists");
    return true;
}