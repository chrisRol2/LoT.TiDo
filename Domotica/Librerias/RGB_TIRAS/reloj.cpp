/*
*	File:	reloj.cpp
*	Author:	Christopher Roldan Sanchez
*	Mail:	Christopher_Rol@hotmail.es
*   Web:    https://www.lot-tido.com
	Created: 4/2/2019 11:18:27 PM
*	Update Date:	05-OCT-2020
*	Description: 
*
*/
#include "reloj.h"


bool reloj_calendario::setHora(int _hora, int _minutos, int _segundos){
	hora_actual = _hora;
	minutos_actual = _minutos;
	segundos_actual = _segundos;	
	return true;
}

bool reloj_calendario::setFecha(int _dia, int _dia_semana, int _mes, int _anio){
	volatile bool fecha_ok =
		(_dia != -1) &&
		(_dia_semana != -1) &&
		(_mes != -1) && 
		(_anio >= 2019);
	if(fecha_ok){
		dia_actual = _dia;
		dia_semana_actual = _dia_semana;
		mes_actual = _mes;
		anio_actual = _anio;
		return true;
	}	
	return false;
}

int reloj_calendario::anio(void) {
	return anio_actual;
}

bool noBlockDelay(unsigned long *time, int delayMillis) {
	if( millis() > *time ) {
		*time = millis() + delayMillis;
		return true;
	}
	return false;
}
bool noBlockDelayMicros(unsigned long *time, int delayMicros) {
	if( micros() > *time ) {
		*time = micros() + delayMicros;
		return true;
	}
	return false;
}

bool noBlockDelayFuncion(unsigned long *time, int delayMillis, 
						 void (*funcion)()) {
	if( millis() > *time ) {
		*time = millis() + delayMillis;
		funcion();
		return true;
	}
	return false;
}