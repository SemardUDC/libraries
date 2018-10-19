#include "Arduino.h"
#include "PCF8591.h"
#define DIRECCION_I2C_PCF8591 0x48

PCF8591 pcf8591(DIRECCION_I2C_PCF8591);

void setup()
{
	Serial.begin(115200);
	pcf8591.iniciar();
}

void loop()
{

	for(int i=0; i<10; i++){
		delay(100);
		Serial.print(".");
	}

	Serial.println("\n");
	int lectura = pcf8591.lecturaAnalogica(ENTRADAA0);
	Serial.print("Entrada Analogica 0 --> ");
	Serial.println(lectura);

	lectura = pcf8591.lecturaAnalogica(ENTRADAA1);
	Serial.print("Entrada Analogica 1 --> ");
	Serial.println(lectura);

	lectura = pcf8591.lecturaAnalogica(ENTRADAA2);
	Serial.print("Entrada Analogica 2 --> ");
	Serial.println(lectura);

	lectura = pcf8591.lecturaAnalogica(ENTRADAA3);
	Serial.print("Entrada Analogica 3 --> ");
	Serial.println(lectura);

}
