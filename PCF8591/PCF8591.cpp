#include "PCF8591.h"
#include "Wire.h"

/**
 * Constructor
 * @param address: i2c address
 */
PCF8591::PCF8591(uint8_t address){
	_address = address;
};
#ifndef __AVR
	/**
	 *
	 * @param address: i2c address
	 * @param sda: sda pin
	 * @param scl: scl pin
	 */
	PCF8591::PCF8591(uint8_t address, uint8_t sda, uint8_t scl){
		_address = address;
		_sda = sda;
		_scl = scl;
	};
#endif

/**
 * wake up i2c controller
 */
void PCF8591::begin(){
	#ifndef __AVR
		Wire.begin(_sda, _scl);
	#else
	//			Default pin for AVR some problem on software emulation
	//			#define SCL_PIN _scl
	// 			#define SDA_PIN _sda
		Wire.begin();
	#endif
}

/**
 * Read one specified channel
 * @param channel channel or analog identify (if readType is SINGLE_ENDED_INPUT)
 * @param readType read datasheet for info
 * 	SINGLE_ENDED_INPUT
 *	TREE_DIFFERENTIAL_INPUT
 *	TWO_SINGLE_ONE_DIFFERENTIAL_INPUT
 * 	TWO_DIFFERENTIAL_INPUT
 * @return
 */
uint8_t PCF8591::analogRead(uint8_t channel, byte readType){
	DEBUG_PRINTLN("Begin trasmission");
	Wire.beginTransmission(_address); // wake up PCF8591

	byte operation = channel | readType| (_outputStatus&OUTPUT_MASK);

	Wire.write(operation); // control byte: reads ADC0 then auto-increment
	Wire.endTransmission(); // end tranmission
	Wire.requestFrom(_address, (uint8_t)2);
	/*uint8_t control = */Wire.read();
	uint8_t ana=Wire.read();

	return ana;
};
