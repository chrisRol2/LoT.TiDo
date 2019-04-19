// WiFi_esp8266.h

#ifndef _WIFI_ESP8266_h
#define _WIFI_ESP8266_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#endif

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
	void refresh();
public:
	reloj_calendarioW(int _husoHorario);
	int hora(void);
	int minutos(void);
	int segundos(void);
	int dia(void);
	int dia_semana(void);
	int mes(void);
	int anio(void);
	int send();

};
class BlynkW {
private:
public:
};
class DHT_Tiempo : public DHTesp {
private:
	int dispositivo;
	int pin;
	float temperaturaCelsius;
	float indiceCalor;
	float humedad;
	
public:
	DHT_Tiempo(int dispositivo) ;
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

};