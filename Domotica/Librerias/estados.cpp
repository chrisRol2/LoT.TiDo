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
#include "luces.h"
#include "pinesIO.h"

display lcd(0x27, VERSION, 4, 20);
wifiN wifi(4);
interrupciones intept(1);
lampara luz_techo(false, false, pin_luz_techo);
lampara luz_balcon(false, false, pin_luz_balcon);
lampara luz_cama(false, false, pin_luz_cama);
lampara luz_labo(false, true, pin_luz_labo);

lampara luz_escritorio(true, pin_RED, pin_GREEN, pin_BLUE);

void estado::config(void) {
	intept.init();
	lcd.init();
	wifi.config();
	lcd.customCharALL();
	lcd.encender(true);

}
void function_test() {
}
void estado::permanente(void) {
	static unsigned long ret = 0, _test = 0;
	intept.temporalizador(1000, &ret, home);
	//intept.temporalizador(500, &_test, function_test);


	return;
}
void estado::select_estado(void) {
	return;
}
void estado::navegador(int maximo, int minimo, int* seleccionador,
	int* menu) {
	return;
}
void estado::home(void) {
	//static unsigned long ret = 0, ret2 = 0;
	static bool control = true;
	lcd.reset();
	if (control) {
		lcd.imprimir(8, 1, "HOME");
		control = false;
		delay(500);
		lcd.clear();
	}
	
	lcd.printHora(0, 0, wifi.getHora(), wifi.getMinutos(),
		wifi.getSegundos());
	lcd.printFecha(6, 0, wifi.getDia(), wifi.getDiaS(), wifi.getMes(),
		wifi.getAnio());
	lcd.printClima(0, 1, wifi.getCelsius(), 0, temperaturaC);
	lcd.printClima(-1, 1, wifi.getHumedad(), 0, temperaturaH);
	lcd.printClima(-1, 1, wifi.getHIC(), 0, temperaturaHIC);
	lcd.printBT(19, 0, wifi.getBtEn());
	lcd.printSimbolo(19, 3, wifi.getDoor());
	lcd.printBatery(19, 2, false);
	lcd.printWiFi(19, 1, wifi.getWifi());
	
}