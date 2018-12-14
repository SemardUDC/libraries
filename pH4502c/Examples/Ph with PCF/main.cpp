// PH meter with PCF8591
// tested on ESP8266
#include <Arduino.h>
#include "pH4502c.h"
#include "PCF8591.h"

// PCF configuration
#define PCF_ADDRESS 0x48
#define PCF_SDA_PIN D2
#define PCF_SCL_PIN D1

PCF8591 pcf48(PCF_ADDRESS, PCF_SDA_PIN, PCF_SCL_PIN);

// PH meter configuration

// Pin number should correspond to an
// available pin at PCF8591.
#define PH_ANALOG_PIN 0

pH4502c ph_meter(pcf48, PH_ANALOG_PIN, [](float_t value) {
    Serial.print("Ph Value is: ");
    Serial.println(value);
});

void setup()
{
    Serial.begin(9600);
    pcf48.iniciar();
}

void loop()
{
    // Reads from the PCF8591 pin configured
    // inside of it.
    ph_meter.handle();
    delay(200);
}