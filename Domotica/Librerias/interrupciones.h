// interrupciones.h

#ifndef _INTERRUPCIONES_h
#define _INTERRUPCIONES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

void i2c_interrupcion(void);
void MQ_2_interrupcion(void);
void pir_interrupcion(void);
void errores(unsigned char error_tipo);
void retraso ( unsigned long tiempo, void funcion());