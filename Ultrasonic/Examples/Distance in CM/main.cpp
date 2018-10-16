#include <Arduino.h>
#include <NewPing.h>
#include <Ultrasonic.h>

const uint8_t TRIGGER_PIN = 10;
const uint8_t ECHO_PIN = 9;
const unsigned int MAX_DISTANCE = 400; // Max distance supported by the sensor.

// Ultrasonic object with trigger and echo pins, max distance and the callback.
Ultrasonic ultrasonic_sensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    delay(50);
    // Gets the current distance in CM
    Serial.print("Distance: ");
    Serial.println(ultrasonic_sensor.currentDistance());
}