#ifndef FLOWMETER_H
#define FLOWMETER_H

#include <Arduino.h>

class FlowMeter
{
  private:
    uint8_t _pin;
    uint _current_content;
    uint _pulse_count;
    uint _last_time;
    float _time_reference; // Sets the calculation intervals from the pulses received.
    byte _last_state;
    float _calibration_factor; // Number of pulses per Liter. Determined by the model.

    void (*_callback)(uint current_content);

    float calculateContent(float flowRate);
    void processCounts();

  public:
    FlowMeter(uint8_t pin, void (*callback)(uint current_content), float calibration_factor = 7.5);
    ~FlowMeter();
    void begin();
    void handle(); // Executes the callback member in the specified _time_reference interval
    void reboot();
    uint getCurrentContent();
};

#endif