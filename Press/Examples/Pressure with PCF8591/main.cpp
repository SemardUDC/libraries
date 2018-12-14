#include <Arduino.h>
#include "Press.h"
#include "PCF8591.h"

// PCF configuration
#define PCF_ADDRESS 0x48
#define PCF_SDA_PIN D2
#define PCF_SCL_PIN D1

PCF8591 pcf48(PCF_ADDRESS, PCF_SDA_PIN, PCF_SCL_PIN);

// pressure sensor configuration

// Pin number should correspond to an
// available pin at PCF8591.
#define PRESS_ANALOG_PIN 1

Press pressure_sensor(PRESS_ANALOG_PIN, pcf48, [](uint16_t kpa) {
    Serial.print("Pressure is: ");
    Serial.print(kpa);
    Serial.println(" kpa");
});

void setup()
{
    Serial.begin(9600);
    pcf48.iniciar();
    pressure_sensor.begin();
}

void loop()
{
    // Invokes the callback with the pressure
    // read as kpa units.
    // Reads from the PCF8591 pin configured
    // inside of it.
    pressure_sensor.handle();
    delay(200);
}
