#include <PCF8574.h>
#include <Electrovalvula.h>

PCF8574 pcf20(0x20);
Electrovalvula valvula1(0, pcf20);
Electrovalvula valvula2(1, pcf20);

void setup()
{
  Serial.begin(9600);
  pcf20.begin();
}

void loop()
{
  delay(1000);
  valvula1.abrir();
  valvula2.cerrar();
  delay(1000);
  valvula1.cerrar([]() {
    Serial.println("Cerrando valvula 1 con callback");
  });
  valvula2.abrir([]() {
    Serial.println("Abriendo valvula 2 con callback");
  });
}