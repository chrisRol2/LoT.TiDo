// 
// 
// 

#include "WiFi_esp8266.h"
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include "Reloj_NTP.h"
#include "DHTesp.h"
#include <Wire.h>
#include "Constantes_i2c.h"
#include <string.h>

const char* ssid = "RSC-2.4GHz";
const char* password = "23554243";
char key_Blynk[] = "8e5c3a46ecc84586bd41462456fd5f42";

int EsclavoDueP = 4;
wifiInternet wifi("RSC-2.4GHz", "23554243");
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
	int clima[] = { 24/*getTempC()*/,90/*getHum()*/,/*getHiC()*/10,
		getViento(),getLuzExterior(),getLluvia(),getLightAPP(),
		getBarometroAPP() };
	const char selectorClima[] = { RECEIVE_TEMP_DHT,
		RECEIVE_HUMEDAD_DHT,RECEIVE_HIC_DHT,RECEIVE_VIENTO,RECEIVE_LUZ_EXT,
		RECEIVE_LLUVIA,RECEIVE_LUX,RECEIVE_BAROMETRO };

	//Serial.println("---------------------------------------");
	for (int i = 0; i < sizeof(clima) / 4; i++) {
		Wire.beginTransmission(4);
		Wire.write(selectorClima[i]);
		Wire.write(clima[i]);
		// 		Serial.print(selectorClima[i]);
		// 		Serial.print(": ");
		// 		Serial.println(clima[i]);
		Wire.endTransmission();
		delayMicroseconds(100);
	}
	//Serial.println("---------------------------------------");	
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
	return indiceCalor;
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
	Wire.begin();
	Serial.begin(74880);
	if (wifi.conectar()) {
		conectar_NTP();
	}
	else {
	}
}
//------------------------ CONFIGURACIONES --------------------------------
//-------------------------------------------------------------------------
//--------------------- RELOJ CALENDARIO NTP ------------------------------
reloj_calendarioW::reloj_calendarioW(int _husoHorario) {
	husoHorario = _husoHorario;
	setZonaHoraria(husoHorario);
	conectar_NTP();

}
void reloj_calendarioW::refresh() {
	getHora(&hora_actual, &minutos_actual, &segundos_actual);
	getFecha(&dia_actual, &dia_semana_actual, &mes_actual, &anio_actual);

}
void reloj_calendarioW::send() {

	refresh();

	Wire.beginTransmission(EsclavoDueP);
	Wire.write(RECEIVE_HORA);
	Wire.write(hora_actual);
	Wire.endTransmission();

	Wire.beginTransmission(EsclavoDueP);
	Wire.write(RECEIVE_MINUTOS);
	Wire.write(minutos_actual);
	Wire.endTransmission();

	Wire.beginTransmission(EsclavoDueP);
	Wire.write(RECEIVE_SEGUNDOS);
	Wire.write(segundos_actual);
	Wire.endTransmission();

	Wire.beginTransmission(EsclavoDueP);
	Wire.write(RECEIVE_DIA);
	Wire.write(dia_actual);
	Wire.endTransmission();

	Wire.beginTransmission(EsclavoDueP);
	Wire.write(RECEIVE_DIA_SEMANA);
	Wire.write(dia_semana_actual);
	Wire.endTransmission();

	Wire.beginTransmission(EsclavoDueP);
	Wire.write(RECEIVE_MES);
	Wire.write(mes_actual);
	Wire.endTransmission();

	Wire.beginTransmission(EsclavoDueP);
	Wire.write(RECEIVE_ANIO);
	Wire.write(anio_actual);
	Wire.endTransmission();

}
//--------------------- RELOJ CALENDARIO NTP ------------------------------
//-------------------------------------------------------------------------
//----------------------- WIFI INTERNET -----------------------------------

bool wifiInternet::conectar() {
	WiFi.mode(WIFI_OFF);
	encender();
	Serial.print("Conectando a: "); Serial.println(ssid);
	WiFi.begin(ssid, password);
	volatile uint8_t rep = 0;
	while (WiFi.status() != WL_CONNECTED) {
		rep++;
		delay(500);
		Serial.print(".");
		if (rep > 20) {
			Serial.println(" ");
			Serial.println("Error al conectar");
			wifi_status();
			WiFi.mode(WIFI_OFF);
			return false;
		}
	}
	Serial.println(" ");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	Serial.print("Se conento exitosamente a: "); Serial.println(ssid);
	wifi_status();
	Blynk.syncAll();
	return true;
}
void wifiInternet::desconetar() {
	Wire.write(RECEIVE_WIFI_STATUS);
	Wire.write(0);
	Wire.endTransmission();
	WiFi.mode(WIFI_OFF); Serial.print("Se desconecto el WIFI: ");
	Serial.println(ssid);
}
void wifiInternet::encender() {
	WiFi.mode(WIFI_STA); Serial.println("Se enciende el WIFI");
}
void wifiInternet::reset() {
	WiFi.mode(WIFI_OFF);
	WiFi.mode(WIFI_STA);
}
void wifiInternet::leer_wifis() {
	Serial.println("SCAN WIFI START");
	reset();
	n_ssid = WiFi.scanNetworks();
}
void wifiInternet::imprimir() {
	for (int i = 0; i < n_ssid; i++) {
		Serial.println("----------------------------------");
		String nombre = WiFi.SSID(i);
		int potencia = WiFi.RSSI(i);
		int seguridad = WiFi.encryptionType(i);
		Serial.print("Wifi: "); Serial.println(nombre);
		Serial.print("Potencia: "); Serial.print(potencia); Serial.println("dBm");
		Serial.print("Seguridad: ");
		Serial.println((seguridad == ENC_TYPE_NONE) ? "Sin Contraseña" : "Con Contraseña");
	}
}
void wifiInternet::seleccionar(int select_n) {
	ssid = WiFi.SSID(select_n);
	password = "23554243";// crear metodo para solicitar password;
	conectar();
	select_wifi = select_n;
}
String wifiInternet::getSSID() {
	return WiFi.SSID();
}
int wifiInternet::getRSSI() {
	return WiFi.RSSI();
}
bool wifiInternet::getEncrypt() {
	if (WiFi.encryptionType(select_wifi) == ENC_TYPE_NONE)return false;
	else return true;
}
bool wifiInternet::status() {
	if (WiFi.status() != WL_CONNECTED) {
		return 0;
	}
	else {
		return 1;
	}
}
void wifi_status(void) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_WIFI_STATUS);
	Wire.write(wifi.status());
	Wire.endTransmission();
}
//----------------------- WIFI INTERNET -----------------------------------
//-------------------------------------------------------------------------
//----------------------- BLYNK CONECT ------------------------------------
BlynkW::BlynkW(char _auth[]) {
	strcpy(auth, _auth);
}
void BlynkW::init(){
	if (wifi.status())Blynk.begin(auth, "Mi WiFi", "wifipass");
}
void BlynkW::run() {
	if (wifi.status()) {
		Blynk.run();
	}
}
WidgetLCD lcd_sist(V9);
int menuSist = 0;
void BlynkW::lcdSist() {
	switch (menuSist) {
	case 1:
		lcd_sist.clear();
		lcd_sist.print(0, 0, wifi.getSSID());
		lcd_sist.print(wifi.getSSID().length() +2, 0, 
			(wifi.getEncrypt()) ? "Segu" : "Inse");
		lcd_sist.print(0, 1, "Potencia: ");
		lcd_sist.print(11, 1,wifi.getRSSI());
		
		break;
	case 2:
		lcd_sist.clear();
		
		break;
	default:
		Serial.println("Error");
	}
}
BLYNK_WRITE(V27){
	menuSist = param.asInt();
	
}
//BLUETOOTH
BLYNK_WRITE(V4){
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_BT_ENABLE);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//LUCES
BLYNK_WRITE(V10) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_LUZ_TECHO);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
BLYNK_WRITE(V11) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_LUZ_CAMA);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
BLYNK_WRITE(V12) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_LUZ_BALCON);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
BLYNK_WRITE(V13) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_LUZ_LABO);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
BLYNK_WRITE(V14) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_NIVEL_LUZ);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//FIN LUCES
//TEMP DESEADA
BLYNK_WRITE(V8) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_TEMP_DESEADA);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//BAROMETRO
BLYNK_WRITE(V17) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_BAROMETRO);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//NIVEL DE LUZ
BLYNK_WRITE(V16) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_LUX);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//CASA GPS
BLYNK_WRITE(V20) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_CASA);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//ESTADO
BLYNK_WRITE(V23) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_ESTADO);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//NAVEGADOR SUBIR
BLYNK_WRITE(V21) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_MOVER_MENU_UP);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//NAVEGADOR BAJAR
BLYNK_WRITE(V22) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_MOVER_MENU_DOWN);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//NAVEGADOR SELECT
BLYNK_WRITE(V24) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_MOVER_MENU_DOWN);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//SELECTOR CLIIMA
BLYNK_WRITE(V7) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_CLIMA_SELECTOR);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//CORTINA
BLYNK_WRITE(V18) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_CORTINA);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//VENTANA
BLYNK_WRITE(V15) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_VENTANA);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//ESTUFA
BLYNK_WRITE(V25) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_ESTUFA);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//TIRA RGB
BLYNK_WRITE(V19) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_TIRA_RGB);
	for (int i = 0; i < 3; i++ )Wire.write(param[i].asInt());
	Wire.endTransmission();
}
//PUERTA
BLYNK_WRITE(V26) {
	Wire.beginTransmission(4);
	Wire.write(RECEIVE_DOOR);
	Wire.write(param.asInt());
	Wire.endTransmission();
}
//----------------------- BLYNK CONECT ------------------------------------
//-------------------------------------------------------------------------
//*/