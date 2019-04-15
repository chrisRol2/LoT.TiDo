/*
 * estados.h
 *
 * Created: 4/2/2019 11:18:27 PM
 * Author:	Christoher Roldan Sanchez
 * Email:	Christopher_rol@hotmail.es
 */ 
#ifndef _ESTADOS_h
#define _ESTADOS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif


class estado{
	private:
		int estado_actual;
		static void home();
	public:
		estado(int _estado_actual): estado_actual(_estado_actual){}
		void config(void);
		void permanente(void);
		void select_estado(void);
		void navegador(int maximo, int minimo, int *seleccionador, int *submenu);
};
