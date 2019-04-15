/*
 * reloj.cpp
 *
 * Created: 4/2/2019 11:18:27 PM
 * Author:	Christoher Roldan Sanchez
 * Email:	Christopher_rol@hotmail.es
 */
#include "reloj.h"


bool reloj_calendario::setHora(int _hora, int _minutos, int _segundos){
	hora_actual = _hora;
	minutos_actual = _minutos;
	segundos_actual = _segundos;	
	return true;
}

bool reloj_calendario::setFecha(int _dia, int _dia_semana, int _mes, int _anio){
	volatile bool fecha_ok = (_dia != -1)&& (_dia_semana != -1) && (_mes != -1) && (_anio >= 2019);
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
