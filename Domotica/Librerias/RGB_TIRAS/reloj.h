/*
*	File:	reloj.h
*	Author:	Christopher Roldan Sanchez
*	Mail:	Christopher_Rol@hotmail.es
*   Web:    https://www.lot-tido.com
*	Created: 4/2/2019 11:18:27 PM
*	Update Date:	05-OCT-2020
*	Description:
*
*/

#ifndef _RELOJ_h
#define _RELOJ_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif


class reloj_calendario{
	private:

		static int timeZone;     // Central European Time
		int timeZone1;     // Central European Time
		//hora
		int horaAlarm;
		int minutoAlarm;
		int segundoAlarm = 0;
		//fecha
		int diaAlarm;
		int mesAlarm;
		int anioAlarm;
		int diaSemanaAlarm;
		bool estado;
		void getHora(char cadena[11]);
		void getFecha(char cadena[11]);
		static time_t getNtpTime();
	public:
		reloj_calendario(int _timeZone);
		bool init();
		void setHora(int _hora, int _minutos);
		void setFecha(int _dia, int _dia_semana, int _mes, int _anio);
		int hora(void);
		int minutos(void);
		int segundos(void);
		int dia(void);
		int dia_semana(void);
		int mes(void);
		int anio(void);
		bool status(void);
		void enable(void);
		void disable(void);
};

bool noBlockDelay(unsigned long *time, int delayMillis);
bool noBlockDelayMicros(unsigned long *time, int delayMicros);
bool noBlockDelayFuncion(unsigned long *time, int delayMillis, 
						 void (*funcion)());