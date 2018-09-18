#include "Arduino.h"
#include "PCF8591.h"
#define PCF8591_I2C_ADDRESS 0x48

PCF8591 pcf8591(PCF8591_I2C_ADDRESS);

void setup()
{
	Serial.begin(115200);
	pcf8591.begin();
}

void loop()
{
	int ana = pcf8591.analogRead(AIN0);
	Serial.print("AIN0 --> ");
	Serial.println(ana);

	ana = pcf8591.analogRead(AIN1);
	Serial.print("AIN1 --> ");
	Serial.println(ana);

	ana = pcf8591.analogRead(AIN2);
	Serial.print("AIN2 --> ");
	Serial.println(ana);

	ana = pcf8591.analogRead(AIN3);
	Serial.print("AIN3 --> ");
	Serial.println(ana);
	delay(3000);

}
