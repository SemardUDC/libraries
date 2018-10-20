#include <FlowMeter.h>

FlowMeter::FlowMeter(uint8_t pin, void (*callback)(uint current_content), float calibration_factor)
    : _pin(pin),
      _callback(callback)
{
    _current_content = 0;
    _pulse_count = 0;
    _last_time = 0;
    _time_reference = 1000.0;
    _calibration_factor = calibration_factor;
    _last_state = LOW;
}

FlowMeter::~FlowMeter() {}

void FlowMeter::begin()
{
    pinMode(_pin, INPUT);
}

void FlowMeter::handle()
{
    const uint time_passed = millis() - _last_time;
    const byte current_state = digitalRead(_pin);
    if ((time_passed) > _time_reference)
    {
        processCounts();
        _last_time = millis();
        _callback(_current_content);
    }
    /*
        As the signals sent by the flow meter tends to be
        always in HIGH or LOW when idle, the only way
        to count the sensor cycles effectively is to capture
        a change from HIGH to LOW and proceed to add 1 to the 
        pulse_count member.
        This avoids making wrong calculations with the signals
        sent by the sensor.
    */
    else if (current_state == LOW && _last_state == HIGH)
    {
        _pulse_count++;
    }
    _last_state = current_state;
}

/*
    Conversion formulas to obtain the rate in L/min
    and calculation to find the content that
    has passed through the sensor were found
    at: 
    https://maker.pro/arduino/tutorial/how-to-interface-arduino-with-flow-rate-sensor-to-measure-liquid
*/
void FlowMeter::processCounts()
{
    const float flowRate = ((_time_reference / (millis() - _last_time)) * _pulse_count) / _calibration_factor;
    _pulse_count = 0;
    _current_content += calculateContent(flowRate);
}

// Returns the content got in 1 second interval in mL
// according to the flow rate.
float FlowMeter::calculateContent(float flowRate)
{
    return (flowRate / 60) * 1000.0;
}

void FlowMeter::reboot()
{
    _pulse_count = 0;
    _current_content = 0;
}

uint FlowMeter::getCurrentContent()
{
    return _current_content;
}