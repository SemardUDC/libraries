#ifndef PCF8591_h
	#define PCF8591_h
	#include "Wire.h"

	#if ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
	#include <math.h>

	#define AIN0 B00000000
	#define AIN1 B00000001
	#define AIN2 B00000010
	#define AIN3 B00000011

	#define ENABLE_OUTPUT B01000000
	#define DISABLE_OUTPUT B01000000

	#define OUTPUT_MASK B01000000

	class PCF8591 {
		public:
			struct AnalogInput {
			   uint8_t ain0;
			   uint8_t ain1;
			   uint8_t ain2;
			   uint8_t ain3;
			} analogInput;

			PCF8591(uint8_t address);

			#ifndef __AVR
				PCF8591(uint8_t address, uint8_t sda, uint8_t scl);
			#endif

			void begin(void);
			uint8_t analogRead(uint8_t channel, byte readType = SINGLE_ENDED_INPUT);

		private:
			uint8_t _address;
			uint8_t _sda = SDA;
			uint8_t _scl = SCL;

			byte _outputStatus = DISABLE_OUTPUT;
	};

#endif
