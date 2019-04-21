// Reloj_NTP.h

#ifndef _RELOJ_NTP_h
#define _RELOJ_NTP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

void conectar_NTP();
void digitalClockDisplay();
void setZonaHoraria(int huso);
void getHora(int *hora, int *minutos,int *segundos);
void getFecha(int *dia, int *dia_semana, int *mes, int *anio);
