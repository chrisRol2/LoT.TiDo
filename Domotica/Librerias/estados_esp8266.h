// estados_esp8266.h

#ifndef _ESTADOS_ESP8266_h
#define _ESTADOS_ESP8266_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif
void temporalizador(unsigned long retraso,
	unsigned long* tiempo_control, void(*funcion)());
class estados {
private:
public:
	estados() {}
	void config();
	void permanente();
	void select_estado();
};
