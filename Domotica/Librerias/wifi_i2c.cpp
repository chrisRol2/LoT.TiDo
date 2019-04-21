/*
 * wifi_i2c.cpp
 *
 * Created: 4/2/2019 11:18:27 PM
 * Author:	Christoher Roldan Sanchez
 * Email:	Christopher_rol@hotmail.es
 */
#include <Wire.h>
#include "wifi_i2c.h"
#include "Constantes_i2c.h"

void receiveEvent(int howMany);
void requestEvent();

int hora = 10, minutos = 0, segundos = 0;
int	dia = 0, diaS = 0, mes = 0, anio = 2019;
int gradosC = 0, hic = 0, humedadP = 0, viento = 0, luz_ext = 0,
	lluvia = 0, lux = 0, barometro = 0;
bool BtEnable = 1, door = 1, WiFiEnable = 1;


int wifiN::getHora(void) {
	return hora;
}
int wifiN::getMinutos(void) {
	return minutos;
}
int wifiN::getSegundos(void) {
	return segundos;
}
int wifiN::getDia(void) {
	return dia;
}
int wifiN::getDiaS(void) {
	return diaS;
}
int wifiN::getMes(void) {
	return mes;
}
int wifiN::getAnio(void) {
	return anio;
}
int wifiN::getCelsius(void) {
	return gradosC;
}
int wifiN::getHumedad(void) {
	return humedadP;
}
int wifiN::getHIC(void) {
	return hic;
}
bool wifiN::getBtEn(void) {
	return BtEnable;
}
bool wifiN::getDoor(void) {
	return door;
}
bool wifiN::getWifi(void) {
	return WiFiEnable;
}

void wifiN::config() {
	Wire1.begin(i2c_dir); 
	Wire1.onReceive(receiveEvent);
	Wire1.onRequest(requestEvent);
}

void receiveEvent(int howMany) {
	volatile char REC = Wire1.read();
	switch (REC) {
	case RECEIVE_HORA:
		hora =  Wire1.read();
		break;
	case RECEIVE_MINUTOS:
		minutos =  Wire1.read();
		break;
	case RECEIVE_SEGUNDOS:
		segundos =  Wire1.read();
		break;
	case RECEIVE_DIA:
		dia =  Wire1.read();
		break;
	case RECEIVE_DIA_SEMANA:
		diaS =  Wire1.read();
		break;
	case RECEIVE_MES:
		mes = Wire1.read();
		break;
	case RECEIVE_ANIO:
		anio =  Wire1.read();
		break;
	case RECEIVE_DOOR:
		door = Wire1.read();
		break;
	case RECEIVE_TEMP_DHT:
		gradosC = Wire1.read();
		break;
	case RECEIVE_VIENTO:
		viento = Wire1.read();
		break;
	case RECEIVE_HUMEDAD_DHT:
		humedadP = Wire1.read();
		break;
	case RECEIVE_LUZ_EXT:
		luz_ext = Wire1.read();
		break;
	case RECEIVE_HIC_DHT:
		hic = Wire1.read();
		break;
	case RECEIVE_BT_ENABLE:
		BtEnable = Wire1.read();
		break;
	case RECEIVE_LLUVIA:
		lluvia = Wire1.read();
		break;
	case RECEIVE_LUX:
		lux = Wire1.read();
		break;
	case RECEIVE_BAROMETRO:
		barometro = Wire1.read();
		break;
	default:
		Serial.println("error");
		volatile int mierda = Wire1.read();
		Serial.println(mierda);
		break;
	}
}

void requestEvent(void) {
	
}
