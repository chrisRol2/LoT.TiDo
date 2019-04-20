// 
// 
// 

#include "estados_esp8266.h"
#include "version.h"
#include "displayLCD.h"
#include "WiFi_esp8266.h"
#include "Wire.h"
DHT_Tiempo climaInte(DHTPIN, DHT_11);
void clima_send(void){
	climaInte.send();
	return;
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
	temporalizador(1000, &temp_ret, clima_send);
	
}