// PCF8574 usage example on
// esp8266.
#include <Arduino.h>
#include "PCF8574.h"

// Parameters for PCF8574
#define PCF_ADDRESS 0x20
#define PCF_SDA D2
#define PCF_SCL D1
#define PCF_PINS_LIMIT 8

// Object creation
PCF8574 pcf(PCF_ADDRESS, PCF_SDA, PCF_SCL);

void activateAllPins();
void deactivateAllPins();
void readAllPins();

void setup()
{
    Serial.begin(9600);
    // Initialize the I2C communication
    pcf.begin();
    Serial.println("Communication initialized....");
}

void loop()
{
    activateAllPins();
    delay(2000);
    readAllPins();
    delay(2000);
    deactivateAllPins();    
    delay(2000);
    readAllPins();
    delay(2000);
}

void activateAllPins()
{
    for (int i = 0; i < PCF_PINS_LIMIT; i++)
    {
        Serial.print("Activating pin: ");
        Serial.println(i);
        pcf.write(i, HIGH);
    }
}

void deactivateAllPins()
{
    for (int i = 0; i < PCF_PINS_LIMIT; i++)
    {
        Serial.print("Deactivating pin: ");
        Serial.println(i);
        pcf.write(i, LOW);
    }
}

void readAllPins()
{
    for(int i = 0; i < PCF_PINS_LIMIT; i++)
    {
        Serial.print("Reading value for pin: ");
        Serial.println(i);
        Serial.println(pcf.read(i));
    }
}