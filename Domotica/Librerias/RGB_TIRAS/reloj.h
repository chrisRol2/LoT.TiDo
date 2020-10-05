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
		int husoHorario;
		int hora_actual;
		int minutos_actual;
		int segundos_actual;
		int dia_actual;
		int dia_semana_actual;
		int mes_actual;
		int anio_actual;
		int getHora();
		int getFecha();
		
	public:
		reloj_calendario(int _husoHorario): husoHorario(_husoHorario){}
		virtual bool setHora(int _hora, int _minutos, int _segundos);
		bool setFecha(int _dia, int _dia_semana, int _mes, int _anio);
		int hora(void);
		int minutos(void);
		int segundos(void);
		int dia(void);
		int dia_semana(void);
		int mes(void);
		int anio(void);		
};

class alarma : private reloj_calendario{
	private:
		bool activado;
		bool repeticion;
		bool repeticion_dia;
		int sonido;
		int rep_tiempo;
	public:
		alarma(int _hora, int _minutos, int _segundos,bool _repeticion, 
			   bool _repeticion_dia, int _sonido, int _repTiempo);
		bool sonar(bool estado = true);
		bool setHora(int _hora, int _minutos, int _segundos);
		void setSonido();
		void setRepDia();
};

bool noBlockDelay(unsigned long *time, int delayMillis);
bool noBlockDelayMicros(unsigned long *time, int delayMicros);
bool noBlockDelayFuncion(unsigned long *time, int delayMillis, 
						 void (*funcion)());