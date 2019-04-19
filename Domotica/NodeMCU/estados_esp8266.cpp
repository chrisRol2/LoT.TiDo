// 
// 
// 

#include "estados_esp8266.h"
#include "version.h"
#include "displayLCD.h"
#include "WiFi_esp8266.h"
DHT_Tiempo climaInte(DHTPIN, DHT_11);


void temporalizador(unsigned long retraso,
	unsigned long* tiempo_control, void(*funcion)()) {
	if (*tiempo_control < millis()) {
		*tiempo_control = retraso + millis();
		funcion();
	}
}

void estados::permanente(){
	static long temp_ret = 90000000;
	//temporalizador(10000, &temp_ret, climaInte.send(0));
}