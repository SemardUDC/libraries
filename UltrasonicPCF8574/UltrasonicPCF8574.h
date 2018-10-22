#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>
// Arduino UNO
#include "PCF8574.h"
#include "NewPingPCF8574.h"

class UltrasonicPCF8574
{
  private:
    NewPingPCF8574 _ultr_sensor;

    uint8_t _trigger_pin;
    uint8_t _echo_pin;
    unsigned int _max_distance;
    unsigned int _current_distance;
    void (*_callback)(unsigned int);

    // Stablishes if the call to NewPing methods will
    // be in cm or median cm. Default to false.
    // This option is evaluated at handle and
    // currentDistance methods.
    bool _median = false;
    // Stablishes how many iterations the median method
    // of NewPing object is going to be executed.
    // Default to 5 iterations.
    unsigned int _iterations = 5;

  public:
    UltrasonicPCF8574(uint8_t trigger_pin, uint8_t echo_pin, unsigned int max_distance, PCF8574 &pcf);
    UltrasonicPCF8574(uint8_t trigger_pin, uint8_t echo_pin, unsigned int max_distance, void (*callback)(unsigned int), PCF8574 &pcf);
    ~UltrasonicPCF8574();

    // Captures and returns the distance in cm using
    // ping_cm method from NewPing member object.
    // Callback is executed.
    unsigned int handle();
    // Captures and returns the distance in cm using
    // ping_cm method from NewPing member object.
    // Callback is not executed.
    unsigned int currentDistance();

    inline void setCallback(void (*callback)(unsigned int))
    {
        this->_callback = callback;
    }

    // Returns median configuration.
    inline bool isMedian()
    {
        return this->_median;
    }
    // Change median configuration.
    inline void setMedian(bool median)
    {
        this->_median = median;
    }

    // Returns the iterations configuration.
    inline unsigned int getIterations()
    {
        return this->_iterations;
    }
    // Change the iterations.
    inline void setIterations(unsigned int iterations)
    {
        this->_iterations = iterations;
    }
};

#endif