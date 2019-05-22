#ifndef _CONFIGURACION_h
#define _CONFIGURACION_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#endif

class iniciar_declarar {
private:
	int Serial_Baud;
	int	bt_Baud;
public:
	iniciar_declarar(int _Serial_Baud,
		int _bt_Baud) : Serial_Baud(_Serial_Baud), bt_Baud(_bt_Baud) {}
	void serial();
	void dispositivos();
	void outputs();
	void inputs();
	void bluetooth();
};
class interrupciones {
private:
	int a;
public:
	interrupciones(int _a) : a(_a) {}
	void init(void);
	void temporalizador(unsigned long retraso,
		unsigned long* tiempo_control, void(*funcion)());
	bool temporalizadorBool(unsigned long retraso,
		unsigned long* tiempo_control);
};
