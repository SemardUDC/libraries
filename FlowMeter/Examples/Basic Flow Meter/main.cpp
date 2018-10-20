#include <Arduino.h>
#include <FlowMeter.h>

const int flow_meter_pin = D1;
void flow_meter_callback(uint current_content)
{
    Serial.print("Current content: ");
    Serial.print(current_content);
    Serial.println(" ml.");
}

FlowMeter flow(flow_meter_pin, flow_meter_callback);
void setup()
{
    Serial.begin(9600);
    flow.begin();
}

void loop()
{
    flow.handle();
}