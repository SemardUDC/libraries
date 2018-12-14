#ifndef NewPingPCF8574_h

	#define NewPingPCF8574_h
	#if defined (ARDUINO) && ARDUINO >= 100
		#include <Arduino.h>
        #include "PCF8574.h"
	#else
		#include <WProgram.h>
		#if defined (PARTICLE)
			#include <SparkIntervalTimer.h>
		#else
			#include <pins_arduino.h>
		#endif
	#endif

	#if defined (__AVR__)
		#include <avr/io.h>
		#include <avr/interrupt.h>
	#endif

	// Shouldn't need to change these values unless you have a specific need to do so.
	#define MAX_SENSOR_DISTANCE 500 // Maximum sensor distance can be as high as 500cm, no reason to wait for ping longer than sound takes to travel this distance and back. Default=500
	#define US_ROUNDTRIP_CM 57      // Microseconds (uS) it takes sound to travel round-trip 1cm (2cm total), uses integer to save compiled code space. Default=57
	#define US_ROUNDTRIP_IN 146     // Microseconds (uS) it takes sound to travel round-trip 1 inch (2 inches total), uses integer to save compiled code space. Defalult=146
	#define ONE_PIN_ENABLED true    // Set to "false" to disable one pin mode which saves around 14-26 bytes of binary size. Default=true
	#define ROUNDING_ENABLED false  // Set to "true" to enable distance rounding which also adds 64 bytes to binary size. Default=false
	#define URM37_ENABLED false     // Set to "true" to enable support for the URM37 sensor in PWM mode. Default=false
	#define TIMER_ENABLED true      // Set to "false" to disable the timer ISR (if getting "__vector_7" compile errors set this to false). Default=true

	// Probably shouldn't change these values unless you really know what you're doing.
	#define NO_ECHO 0               // Value returned if there's no ping echo within the specified MAX_SENSOR_DISTANCE or max_cm_distance. Default=0
	#define MAX_SENSOR_DELAY 5800   // Maximum uS it takes for sensor to start the ping. Default=5800
	#define ECHO_TIMER_FREQ 24      // Frequency to check for a ping echo (every 24uS is about 0.4cm accuracy). Default=24
	#define PING_MEDIAN_DELAY 29000 // Microsecond delay between pings in the ping_median method. Default=29000
	#define PING_OVERHEAD 5         // Ping overhead in microseconds (uS). Default=5
	#define PING_TIMER_OVERHEAD 13  // Ping timer overhead in microseconds (uS). Default=13
	#if URM37_ENABLED == true
		#undef  US_ROUNDTRIP_CM
		#undef  US_ROUNDTRIP_IN
		#define US_ROUNDTRIP_CM 50  // Every 50uS PWM signal is low indicates 1cm distance. Default=50
		#define US_ROUNDTRIP_IN 127 // If 50uS is 1cm, 1 inch would be 127uS (50 x 2.54 = 127). Default=127
	#endif

	// Conversion from uS to distance (round result to nearest cm or inch).
	#define NewPingPCF8574Convert(echoTime, conversionFactor) (max(((unsigned int)echoTime + conversionFactor / 2) / conversionFactor, (echoTime ? 1 : 0)))

	// Detect non-AVR microcontrollers (Teensy 3.x, Arduino DUE, etc.) and don't use port registers or timer interrupts as required.
	#if (defined (__arm__) && (defined (TEENSYDUINO) || defined (PARTICLE)))
		#undef  PING_OVERHEAD
		#define PING_OVERHEAD 1
		#undef  PING_TIMER_OVERHEAD
		#define PING_TIMER_OVERHEAD 1
		#define DO_BITWISE true
	#elif !defined (__AVR__)
		#undef  PING_OVERHEAD
		#define PING_OVERHEAD 1
		#undef  PING_TIMER_OVERHEAD
		#define PING_TIMER_OVERHEAD 1
		#undef  TIMER_ENABLED
		#define TIMER_ENABLED false
		#define DO_BITWISE false
	#else
		#define DO_BITWISE true
	#endif

	// Disable the timer interrupts when using ATmega128 and all ATtiny microcontrollers.
	#if defined (__AVR_ATmega128__) || defined (__AVR_ATtiny24__) || defined (__AVR_ATtiny44__) || defined (__AVR_ATtiny441__) || defined (__AVR_ATtiny84__) || defined (__AVR_ATtiny841__) || defined (__AVR_ATtiny25__) || defined (__AVR_ATtiny45__) || defined (__AVR_ATtiny85__) || defined (__AVR_ATtiny261__) || defined (__AVR_ATtiny461__) || defined (__AVR_ATtiny861__) || defined (__AVR_ATtiny43U__)
		#undef  TIMER_ENABLED
		#define TIMER_ENABLED false
	#endif

	// Define timers when using ATmega8, ATmega16, ATmega32 and ATmega8535 microcontrollers.
	#if defined (__AVR_ATmega8__) || defined (__AVR_ATmega16__) || defined (__AVR_ATmega32__) || defined (__AVR_ATmega8535__)
		#define OCR2A OCR2
		#define TIMSK2 TIMSK
		#define OCIE2A OCIE2
	#endif

	class NewPingPCF8574 {
		public:
            NewPingPCF8574(uint8_t trigger_pin, uint8_t echo_pin, unsigned int max_cm_distance, PCF8574 &pcf);
			unsigned int ping(unsigned int max_cm_distance = 0);
			unsigned long ping_cm(unsigned int max_cm_distance = 0);
			unsigned long ping_in(unsigned int max_cm_distance = 0);
			unsigned long ping_median(uint8_t it = 5, unsigned int max_cm_distance = 0);
			static unsigned int convert_cm(unsigned int echoTime);
			static unsigned int convert_in(unsigned int echoTime);
	#if TIMER_ENABLED == true
			void ping_timer(void (*userFunc)(void), unsigned int max_cm_distance = 0);
			boolean check_timer();
			unsigned long ping_result;
			static void timer_us(unsigned int frequency, void (*userFunc)(void));
			static void timer_ms(unsigned long frequency, void (*userFunc)(void));
			static void timer_stop();
	#endif
		private:
			boolean ping_trigger();
			void set_max_distance(unsigned int max_cm_distance);
	#if TIMER_ENABLED == true
			boolean ping_trigger_timer(unsigned int trigger_delay);
			boolean ping_wait_timer();
			static void timer_setup();
			static void timer_ms_cntdwn();
	#endif
	#if DO_BITWISE == true
			uint8_t _triggerBit;
			uint8_t _echoBit;
		#if defined(PARTICLE)
			#if !defined(portModeRegister)
				#if defined (STM32F10X_MD)
					#define portModeRegister(port)     ( &(port->CRL) )
				#elif defined (STM32F2XX)
					#define portModeRegister(port)     ( &(port->MODER) )
				#endif
			#endif
			volatile uint32_t *_triggerOutput;
			volatile uint32_t *_echoInput;
			volatile uint32_t *_triggerMode;
		#else
			volatile uint8_t *_triggerOutput;
			volatile uint8_t *_echoInput;
			volatile uint8_t *_triggerMode;
		#endif
	#else
			uint8_t _triggerPin;
			uint8_t _echoPin;
	#endif
			unsigned int _maxEchoTime;
			unsigned long _max_time;
            PCF8574 &_pcf;
	};


#endif