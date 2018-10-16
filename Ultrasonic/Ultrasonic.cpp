#include <Ultrasonic.h>


Ultrasonic::Ultrasonic(uint8_t trigger_pin, uint8_t echo_pin, unsigned int max_distance)
    : _trigger_pin(trigger_pin),
      _echo_pin(echo_pin),
      _max_distance(max_distance),
      _callback(0),
      // NewPing object is initialized.
      _ultr_sensor(trigger_pin, echo_pin, max_distance)
{
    this->_current_distance = 0;
}
Ultrasonic::Ultrasonic(uint8_t trigger_pin, uint8_t echo_pin, unsigned int max_distance, void (*callback)(unsigned int))
    : _trigger_pin(trigger_pin),
      _echo_pin(echo_pin),
      _max_distance(max_distance),
      _callback(callback),
      // NewPing object is initialized.
      _ultr_sensor(trigger_pin, echo_pin, max_distance)
{
    this->_current_distance = 0;
}

Ultrasonic::~Ultrasonic() {}

unsigned int Ultrasonic::handle()
{
    unsigned int captured_distance = 0;

    if (this->_median)
    {
        // Gets a ping in ms with a median according to the iterations
        // stablished and is converted to cm with convert_cm() method.
        captured_distance = this->_ultr_sensor.convert_cm(this->_ultr_sensor.ping_median(this->_iterations));
    }
    else
    {
        captured_distance = this->_ultr_sensor.ping_cm();
    }

    this->_current_distance = captured_distance;

    // Executes the callback.
    this->_callback(this->_current_distance);
    return this->_current_distance;
}

unsigned int Ultrasonic::currentDistance()
{
    unsigned int captured_distance = 0;

    if (this->_median)
    {
        // Gets a ping in ms with a median according to the iterations
        // stablished and is converted to cm with convert_cm() method.
        captured_distance = this->_ultr_sensor.convert_cm(this->_ultr_sensor.ping_cm(this->_iterations));
    }
    else
    {
        captured_distance = this->_ultr_sensor.ping_cm();
    }

    this->_current_distance = captured_distance;
    return this->_current_distance;
}