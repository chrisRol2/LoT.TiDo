/*
 * estados.cpp
 *
 * Created: 4/2/2019 11:18:27 PM
 * Author:	Christoher Roldan Sanchez
 * Email:	Christopher_rol@hotmail.es
 */
#include "estados.h"
#include <list>
#include "version.h"
#include "displayLCD.h"
#include "wifi_i2c.h"
#include "configuracion.h"
display lcd(0x27, VERSION, 4, 20);
wifiN wifi(4);
interrupciones intept(1);
void estado::config(void) {
	intept.init();
	lcd.init();
	wifi.config();
	lcd.customCharALL();
	lcd.encender(true);
}



void estado::permanente(void) {
	static unsigned long ret = 0;
	intept.temporalizador(1000, &ret, home);
	return;
}
void estado::select_estado(void) {
	return;
}
void estado::navegador(int maximo, int minimo, int* seleccionador, int* menu) {
	return;
}
void estado::home(void) {
	lcd.reset();
	lcd.printHora(0, 0, wifi.getHora(), wifi.getMinutos(),
		wifi.getSegundos());
	lcd.printFecha(6, 0, wifi.getDiaS(), wifi.getDia(), wifi.getMes(),
		wifi.getAnio());
	lcd.printClima(0, 1, wifi.getCelsius(), 0, temperaturaC);
	lcd.printClima(-1, 1, wifi.getHumedad(), 0, temperaturaH);
	lcd.printClima(-1, 1, wifi.getHIC(), 0, temperaturaHIC);
	lcd.printBT(19, 0, wifi.getBtEn());
	lcd.printSimbolo(19, 3, wifi.getDoor());
	lcd.printWiFi(19, 1, wifi.getWifi());
}