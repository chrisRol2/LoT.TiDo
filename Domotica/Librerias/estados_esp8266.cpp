// 
// 
// 

#include "estados_esp8266.h"
#include "version.h"
#include "displayLCD.h"

void temporalizador(unsigned long retraso,
	unsigned long* tiempo_control, void(*funcion)()) {
	if (*tiempo_control < millis()) {
		*tiempo_control = retraso + millis();
		funcion();
	}
}

void estado::permanente(){
	

}