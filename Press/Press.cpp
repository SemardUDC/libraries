#include <Press.h>

#ifdef PRESS_DEBUG
#define PRESS_DEBUG_PRINT(String) (Serial.println(String))
#endif

#ifndef PRESS_DEBUG
#define PRESS_DEBUG_PRINT(String)

#endif

Press::Press(uint8_t _pin, void (*_callBackFunction)(uint16_t kpa))
    : pin(_pin), pcf(nullptr), callBackFunction(_callBackFunction),
    analog_v(0), mpa(0), kpa(0), psi(0)
{}

Press::Press(uint8_t _pin, PCF8591 &_pcf, void (*_callBackFunction)(uint16_t kpa))
    : pin(_pin), pcf(&_pcf), callBackFunction(_callBackFunction),
    analog_v(0), mpa(0), kpa(0), psi(0)
{}

Press::~Press()
{
    PRESS_DEBUG_PRINT("Deleting Press Object");
}

void Press::begin()
{
    if (!pcf)
        pinMode(pin, INPUT);
    PRESS_DEBUG_PRINT("Initializing Pin ");
    check_CallBackFunction(); //VOID
}

void Press::handle()
{
    float press_MPa = 0;
    if (pcf)
    {
        analog_v = pcf->lecturaAnalogica(pin);
        // Evaluar ecuación con PCF. Las especificaciones
        // cambian debido a que el pcf arroja señales de hasta
        // 3.3v, afectando el rango de salida del sensor
        // de 0.5 - 4.5V. Además, el rango de valores análogos
        // se da entre 0 - 254.
        // La ecuación representa el paso del rango 0 - 1023
        // a 0 - 255 teniendo en cuenta la operación entre 
        // 102 - 921.
        press_MPa = (((analog_v - 25) * 1.2) / 201);
    }
    else if (!pcf)
    {
        analog_v = analogRead(pin);
        // Teniendo que el sensor arroja una señal análoga
        // con V entre 0.5 - 4.5 para valores de MPa entre
        // 0 - 1.2.
        // La ecuación tiene en cuenta esos rangos y calcula
        // el mpa de acuerdo a las prestaciones del sensor.
        // Se asume que cuando no se usa pcf, el pin análogo
        // opera en un rango de 0 - 1023.
        // Sin embargo, evaluación hay que hacerse debido
        // a que el ESP A0 soporta hasta 3.3v.
        press_MPa = (((analog_v - 102) * 1.2) / 818);
    }
    
    float press_kPa = press_MPa * 1000;
    float press_psi = press_kPa * 0.14503773773020923; /*
    PRESS_DEBUG_PRINT("The pressure is "+press_MPa+"MPa.");
    PRESS_DEBUG_PRINT("The pressure is "+press_kPa+"kPa.");
    PRESS_DEBUG_PRINT("The pressure is "+press_psi+"psi."); */

    this->mpa = press_MPa;
    this->kpa = press_kPa;
    this->psi = press_psi;

    if (callBackFunction)
        callBackFunction(kpa);
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