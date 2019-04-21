// WiFi_esp8266.h

#ifndef _WIFI_ESP8266_h
#define _WIFI_ESP8266_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#endif
#define DHT_11 1
#define DHT_22 2

#define D0 16

#define DHTPIN 16
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
class config{
private:
	int esclavo_due;
public:
	config(int _esclavo_due);
	void init();
};
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
class wifiInternet {
private:
public:
	void conectar();
	void desconetar();
	void leer_wifis();
	void controlar();
	void seleccionar();
	void imprimir();
	void getSSID();
	void getRSSI();
	void getEncrypt();
};
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//--------------------- RELOJ CALENDARIO NTP ------------------------------
class reloj_calendarioW {
private:
	int husoHorario;
	int hora_actual;
	int minutos_actual;
	int segundos_actual;
	int dia_actual;
	int dia_semana_actual;
	int mes_actual;
	int anio_actual;
	void refresh(void);
public:
	reloj_calendarioW(int _husoHorario);
	int hora(void);
	int minutos(void);
	int segundos(void);
	int dia(void);
	int dia_semana(void);
	int mes(void);
	int anio(void);
	int send(void);
};
//--------------------- RELOJ CALENDARIO NTP ------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
class BlynkW {
private:
public:
};
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//------------------------ DHT SENSOR READ --------------------------------
class DHT_Tiempo{
private:
	int dispositivo;
	int pin;
	int temperaturaCelsius;
	int indiceCalor;
	int humedad;
	int viento;
	int luzExterior;
	int luzAPP;
	int presion;
	
public:
	DHT_Tiempo(int dispositivo, int pin) ;
	int getTempC();
	int	getTempF();
	int	getHum();
	int	getHiC();
	int getViento();
	int getLuzExterior();
	int getLluvia();
	int getLightAPP();
	int setLightAPP(int light);
	int getBarometroAPP();
	int setBarometroAPP(int press);
	void send();
	void refresh();

};
//------------------------DHT SENSOR READ----------------------------------
//-------------------------------------------------------------------------