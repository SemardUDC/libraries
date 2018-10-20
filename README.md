# libraries
Conjunto de librerias para componentes embebidos con el framework Arduino.

# Componentes
## Electrovalvula
Se encarga de la apertura y cierre electrónico de las válvulas usando un expansor I2C de tipo PCF8574.
* Dependencias
  * Clase PCF8574 *misma librería*
## Press
Clase encargada de la lectura de un sensor de presión y la muestra de los mismos en diferentes unidades como kPa, mPa y psi.
## PCF8591
Se utiliza para hacer la lectura de los diferentes sensores del sistema, y se encarga de enviar la información al microcontrolador por medio del bus I2C.
* Dependencias
  * Clase Wire (oficial de Arduino)
## PCF8574
Encargado de manejar la expansión de pines digitales por medio del bus I2C. Envolvente de la librería pcf8574 usada como dependencia, realizada para añadir funcionalidad para gestionar comunicación con múltiples buses.
* Dependencias
  * Libería [pcf8574_esp](https://github.com/WereCatf/PCF8574_ESP).
## Ultrasonic
Libreria para la manipulación de sensor de ultrasonido para obtención de medidas de distancia en cm. Probado en sensor JSN-SR04t.
* Dependencias
  * Librería [NewPing](https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home)
## FlowMeter
Librería para manipular sensor de flujo de agua para obtener la cantidad de agua en mL. Probado en sensor YF-S201.
## pH4502c
Librería para manipular el sensor de PH formado por una sonda de electrodo BNC y el módulo de sensor de detección pH4502c.