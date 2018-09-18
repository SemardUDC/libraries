#ifndef PCF8591_h
	#define PCF8591_h
	#include "Wire.h"

	#if ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
	#include <math.h>

	#define ENTRADAA0 B00000000
	#define ENTRADAA1 B00000001
	#define ENTRADAA2 B00000010
	#define ENTRADAA3 B00000011

	#define ENTR_FINAL_UNITARIO B00000000

	#define HABILITAR_SALIDA B01000000
	#define DESHABILITAR_SALIDA B01000000

	#define MASCARA_DE_SALIDA B01000000

	class PCF8591 {
		public:
			struct EntradaAnalogica {
			   uint8_t ea0;
			   uint8_t ea1;
			   uint8_t ea2;
			   uint8_t ea3;
			} entradaAnalogica;

			PCF8591(uint8_t direccion);

			#ifndef __AVR
				PCF8591(uint8_t direccion, uint8_t sda, uint8_t scl);
			#endif

			void iniciar(void);
			uint8_t lecturaAnalogica(uint8_t canal, byte leerTipo = ENTR_FINAL_UNITARIO);

		private:
			uint8_t _direccion;
			uint8_t _sda = SDA;
			uint8_t _scl = SCL;

			byte _estadoDeSalida = DESHABILITAR_SALIDA;
	};

#endif
