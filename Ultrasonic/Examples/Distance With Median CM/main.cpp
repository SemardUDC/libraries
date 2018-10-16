#include <Arduino.h>
#include <NewPing.h>
#include <Ultrasonic.h>

const uint8_t TRIGGER_PIN = 10;
const uint8_t ECHO_PIN = 9;
const unsigned int MAX_DISTANCE = 400; // Max distance supported by the sensor.

// Callback executed by the Ultrasonic's handle method
// with the captured distance.
void ultrasonic_callback(unsigned int distance)
{
    Serial.print("Distance from callback: ");
    Serial.println(distance);
}

// Ultrasonic object with trigger and echo pins, max distance and the callback.
Ultrasonic ultrasonic_sensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE, ultrasonic_callback);

void setup()
{
    Serial.begin(115200);
    // Activates the median values
    ultrasonic_sensor.setMedian(true);
    ultrasonic_sensor.setIterations(10);
}

void loop()
{
    delay(50);
    ultrasonic_sensor.handle(); // gets distance in cm and executes the callback.
}