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
	String ssid;
	String password;
	int n_ssid;
	int select_wifi = 1;
public:
	wifiInternet(String _ssid, String _password) : ssid(_ssid),
		password(_password) {}
	bool conectar();
	void encender();
	void desconetar();
	void reset();
	void leer_wifis();
	void imprimir();
	void seleccionar(int select_n);
	String getSSID();
	int getRSSI();
	bool getEncrypt();
	void setSSID();
	void setRSSI();	
	bool status();
};
void wifi_status(void);
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
	void send(void);
};
//--------------------- RELOJ CALENDARIO NTP ------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
class BlynkW {
private:
	char auth[];
public:
	BlynkW(char _auth[]);
	void run();
	void init();
	void lcdSist();
	void reconectar();
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
//----------------------- Bt status ---------------------------------------

class bt_status {
private:
public:
};