#include "PCF8591.h"
#include "Wire.h"

PCF8591::PCF8591(uint8_t direccion){
	_direccion = direccion;
};
#ifndef __AVR
	PCF8591::PCF8591(uint8_t direccion, uint8_t sda, uint8_t scl){
		_direccion = direccion;
		_sda = sda;
		_scl = scl;
	};
#endif

void PCF8591::iniciar(){
	#ifndef __AVR
		Wire.begin(_sda, _scl);
	#else
		Wire.begin();
	#endif
}

uint8_t PCF8591::lecturaAnalogica(uint8_t canal, byte leerTipo){
	Wire.beginTransmission(_direccion);

	byte operacion = canal | leerTipo| (_estadoDeSalida&MASCARA_DE_SALIDA);

	Wire.write(operacion);
	Wire.endTransmission();
	Wire.requestFrom(_direccion, (uint8_t)2);
	Wire.read();
	uint8_t lectura=Wire.read();

	return lectura;
};
