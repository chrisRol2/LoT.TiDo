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

int hora = -1, minutos = -1, segundos = -1;
int	dia = -1, diaS = -1, mes = -1, anio = -1;
int gradosC = -90, hic = -90, humedadP = -1;
bool BtEnable = 0, door = 0, WiFiEnable = 0;


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

}

void requestEvent(void) {
	volatile unsigned char REC = Wire1.read();

	switch (REC) {
	case RECEIVE_HORA:
		hora = Wire1.read();
		break;
	case RECEIVE_MINUTOS:
		minutos = Wire1.read();
		break;
	case RECEIVE_SEGUNDOS:
		segundos = Wire1.read();
		break;
	case RECEIVE_DIA:
		dia = Wire1.read();
		break;
	case RECEIVE_DIA_SEMANA:
		diaS = Wire1.read();
		break;
	case RECEIVE_MES:
		mes = Wire1.read();
		break;
	case RECEIVE_ANIO:
		anio = Wire1.read();
		break;
	case RECEIVE_TIRA_RGB:
		break;
	case RECEIVE_ESTUFA:
		break;
	case RECEIVE_LUX:
		break;
	case RECEIVE_NIVEL_LUZ:
		break;
	case RECEIVE_BAROMETRO:
		break;
	case RECEIVE_CASA:
		break;
	case RECEIVE_TEMP_DESEADA:
		break;
	case RECEIVE_DOOR:
		door = Wire1.read();
		break;
	case RECEIVE_TEMP_DHT:
		gradosC = Wire1.read();
		break;
	case RECEIVE_HUMEDAD_DHT:
		humedadP = Wire1.read();
		break;
	case RECEIVE_HIC_DHT:
		hic = Wire1.read();
		break;
	case RECEIVE_BT_ENABLE:
		BtEnable = Wire1.read();
		break;
	case RECEIVE_ESTADO:
		break;
	case RECEIVE_MOVER_MENU:
		break;
		// 	case:
		// 		break;
	default:
		break;
	}
}
