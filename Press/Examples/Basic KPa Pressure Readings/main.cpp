#include <Arduino.h>
#include "Press.h"

#define PRESS_ANALOG_PIN A0

Press pressure_sensor(PRESS_ANALOG_PIN, [](uint16_t kpa) {
    Serial.print("Pressure is: ");
    Serial.print(kpa);
    Serial.println(" kpa");
});

void setup()
{
    Serial.begin(9600);
    pressure_sensor.begin();
}

void loop()
{
    // Invokes the callback with the pressure
    // read as kpa units.
    pressure_sensor.handle();
    delay(200);
}
