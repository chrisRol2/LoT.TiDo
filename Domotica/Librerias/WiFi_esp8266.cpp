// 
// 
// 

#include "WiFi_esp8266.h"

#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include "Reloj_NTP.h"
#include "DHTesp.h"
#include <Wire.h>

int EsclavoDueP = 4;
//------------------------ DHT SENSOR READ --------------------------------
DHTesp dht;
DHT_Tiempo::DHT_Tiempo(int dispositivo, int pin) {
	switch (dispositivo) {
	case 1:
		dht.setup(pin, DHTesp::DHT11);
	case 2:
		dht.setup(pin, DHTesp::DHT22);
	default:
		Serial.println("Error al inicializar DHT");
	}

}
void DHT_Tiempo::send() {
	int clima[] = { getTempC(),getTempF(),getHum(),getHiC(),
		getViento(),getLuzExterior(),getLluvia(),getLightAPP(),
		getBarometroAPP() };
	const char selectorClima[] = { 't','f','h','H','X','v','l','L','P' };
	Wire.beginTransmission(EsclavoDueP);
	Serial.println("---------------------------------------");
	for (int i = 0; i < sizeof(clima) / 4; i++) {
		Wire.write(selectorClima[i]);
		Wire.write(clima[i]);
		Serial.println(" ");
		Serial.print(selectorClima[i]);
		Serial.print(": ");
		Serial.println(clima[i]);
		Serial.println(" ");
	}
	Serial.println("---------------------------------------");
	Wire.endTransmission();

}
void DHT_Tiempo::refresh() {

}
int DHT_Tiempo::getTempC() {
	temperaturaCelsius = dht.getTemperature();
	return temperaturaCelsius;
}
int DHT_Tiempo::getHum() {
	humedad = dht.getHumidity();
	return humedad;
}
int DHT_Tiempo::getTempF() {
	return dht.toFahrenheit(temperaturaCelsius);
}
int DHT_Tiempo::getHiC() {
	indiceCalor = dht.computeHeatIndex(temperaturaCelsius, humedad, false);
}
int DHT_Tiempo::getViento() {
	return viento;
}
int DHT_Tiempo::getLluvia() {
	return 0;
}
int DHT_Tiempo::getLuzExterior() {
	return luzExterior;
}
int DHT_Tiempo::getLightAPP() {
	return luzAPP;
}
int DHT_Tiempo::getBarometroAPP() {
	return presion;
}
//------------------------DHT SENSOR READ----------------------------------
//-------------------------------------------------------------------------
//------------------------ CONFIGURACIONES --------------------------------
config::config(int _esclavo_due) {
	esclavo_due = _esclavo_due;
	EsclavoDueP = esclavo_due;

}
void config::init() {
	Wire.begin(74880);
	Serial.begin(74880);
	Wire.beginTransmission(4);
	Wire.write('t');
	Wire.write(20);
	Wire.endTransmission();
}
//------------------------ CONFIGURACIONES --------------------------------
//-------------------------------------------------------------------------
//--------------------- RELOJ CALENDARIO NTP ------------------------------

//--------------------- RELOJ CALENDARIO NTP ------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
