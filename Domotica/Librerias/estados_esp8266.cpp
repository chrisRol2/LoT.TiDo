// 
// 
// 

#include "estados_esp8266.h"
#include "version.h"
//#include "displayLCD.h"
#include "WiFi_esp8266.h"
#include "Wire.h"
#include "Reloj_NTP.h"
DHT_Tiempo climaInte(DHTPIN, DHT_11);
reloj_calendarioW reloj(-3);

void clima_send(void){
	climaInte.send();
	return;
}
void reloj_send(void) {
	reloj.send();
}

void temporalizador(unsigned long retraso,
	unsigned long* tiempo_control, void(*funcion)()) {
	if (*tiempo_control < millis()) {
		*tiempo_control = retraso + millis();
		funcion();
	}
}

void estados::permanente(){
	static unsigned long temp_ret = 9000;
	static unsigned long reloj_ret = 8500;
	temporalizador(1000, &temp_ret, clima_send);
	temporalizador(1000, &reloj_ret, reloj_send);
	
}