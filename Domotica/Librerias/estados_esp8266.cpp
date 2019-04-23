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
BlynkW APP("8e5c3a46ecc84586bd41462456fd5f42");

void clima_send(void){
	climaInte.send();
	return;
}
void reloj_send(void) {
	reloj.send();
}
void app_run(){
	APP.run();
}
void app_lcd_sist(){
	APP.lcdSist();
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
	static unsigned long wifi_ret = 9050;
	static unsigned long lcdSist_ret = 1000;
	temporalizador(1000, &temp_ret, clima_send);
	temporalizador(1000, &reloj_ret, reloj_send);
	temporalizador(5000, &wifi_ret, wifi_status);
	temporalizador(60000, &lcdSist_ret, app_lcd_sist);
	APP.run();
	
}
void  estados::config(){
	APP.init();
}