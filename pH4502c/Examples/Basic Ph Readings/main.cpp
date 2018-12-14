#include <Arduino.h>
#include "pH4502c.h"

#define PH_ANALOG_PIN A0

pH4502c ph_meter(PH_ANALOG_PIN, [](float_t value) {
    Serial.print("Ph Value is: ");
    Serial.println(value);
});

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    ph_meter.handle();
    delay(200);
}