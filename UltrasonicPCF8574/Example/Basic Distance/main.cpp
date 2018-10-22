#include <Arduino.h>
#include <NewPingPCF8574.h>
#include <UltrasonicPCF8574.h>
#include "PCF8574.h"

PCF8574 pcf(0x20, D2, D1);

const uint8_t TRIGGER_PIN = 0;
const uint8_t ECHO_PIN = 1;
const unsigned int MAX_DISTANCE = 400; // Max distance supported by the sensor.

// Callback executed by the Ultrasonic's handle method
// with the captured distance.
void ultrasonic_callback(unsigned int distance)
{
    Serial.print("Distance from callback: ");
    Serial.println(distance);
}

// Ultrasonic object with trigger and echo pins, max distance and the callback.
UltrasonicPCF8574 ultrasonic_sensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE, ultrasonic_callback, pcf);

int oldTime = 0;
bool state = true;
void setup()
{
    Serial.begin(9600);
    // Activates the median values
    ultrasonic_sensor.setMedian(true);
    ultrasonic_sensor.setIterations(10);
    pcf.begin();
}

void loop()
{
    delay(50);
    ultrasonic_sensor.handle();
}