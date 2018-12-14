// Sketch that handles two I2C
// pcf components on ESP8266.
#include <Arduino.h>
#include "PCF8574.h"

// Pins supported by PCF8574
#define PCF_PINS_LIMIT 8

// Constructor Format
// Address, SDA_pin, SCL_pin, multiple I2C support
const int addresses[2] = {0x20, 0x27};
const int sda_pins[2] = {D2, D6};
const int scl_pins[2] = {D1, D7};
const bool multiple_I2C = true;

// PCFs instantiation
// The last parameter indicates the behavior of the pcf
// against multiple I2C channels of communication being handled
// by the ESP8266
PCF8574 pcf20(addresses[0], sda_pins[0], scl_pins[0], multiple_I2C);
PCF8574 pcf27(addresses[1], sda_pins[1], scl_pins[1], multiple_I2C);

void activateAllPins(PCF8574 &pcf);
void deactivateAllPins(PCF8574 &pcf);

void setup()
{
    Serial.begin(9600);
    pcf20.begin();
    pcf27.begin();
    Serial.println("PCFs initialized...");
}

void loop()
{
    activateAllPins(pcf20);
    delay(2000);
    deactivateAllPins(pcf20);
    delay(2000);
    activateAllPins(pcf27);
    delay(2000);
    deactivateAllPins(pcf27);
    delay(2000);
}

void activateAllPins(PCF8574 &pcf)
{    
    for(int i = 0; i < PCF_PINS_LIMIT; i++)
    {
        Serial.print("Activating pin: ");
        Serial.println(i);
        pcf.write(i, HIGH);
    }    
}

void deactivateAllPins(PCF8574 &pcf)
{
    for(int i = 0; i < PCF_PINS_LIMIT; i++)
    {
        Serial.print("Deactivating pin: ");
        Serial.println(i);
        pcf.write(i, LOW);
    }
}