#include <UltrasonicPCF8574.h>


UltrasonicPCF8574::UltrasonicPCF8574(uint8_t trigger_pin, uint8_t echo_pin, unsigned int max_distance, PCF8574 &pcf)
    : _trigger_pin(trigger_pin),
      _echo_pin(echo_pin),
      _max_distance(max_distance),
      _callback(0),
      // NewPing object is initialized.
      _ultr_sensor(trigger_pin, echo_pin, max_distance, pcf)
{
    _current_distance = 0;
}
UltrasonicPCF8574::UltrasonicPCF8574(uint8_t trigger_pin, uint8_t echo_pin, unsigned int max_distance, void (*callback)(unsigned int), PCF8574 &pcf)
    : _trigger_pin(trigger_pin),
      _echo_pin(echo_pin),
      _max_distance(max_distance),
      _callback(callback),
      // NewPing object is initialized.
      _ultr_sensor(trigger_pin, echo_pin, max_distance, pcf)
{
    _current_distance = 0;
}

UltrasonicPCF8574::~UltrasonicPCF8574() {}

unsigned int UltrasonicPCF8574::handle()
{
    unsigned int captured_distance = 0;

    if (_median)
    {
        // Gets a ping in ms with a median according to the iterations
        // stablished and is converted to cm with convert_cm() method.
        captured_distance = _ultr_sensor.convert_cm(_ultr_sensor.ping_median(_iterations));
    }
    else
    {
        captured_distance = _ultr_sensor.ping_cm();
    }

    _current_distance = captured_distance;

    // Executes the callback.
    _callback(_current_distance);
    return _current_distance;
}

unsigned int UltrasonicPCF8574::currentDistance()
{
    unsigned int captured_distance = 0;

    if (_median)
    {
        // Gets a ping in ms with a median according to the iterations
        // stablished and is converted to cm with convert_cm() method.
        captured_distance = _ultr_sensor.convert_cm(_ultr_sensor.ping_cm(_iterations));
    }
    else
    {
        captured_distance = _ultr_sensor.ping_cm();
    }

    _current_distance = captured_distance;
    return _current_distance;
}