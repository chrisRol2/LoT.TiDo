/*
*	File:	reloj.cpp
*	Author:	Christopher Roldan Sanchez
*	Mail:	Christopher_Rol@hotmail.es
*   Web:    https://www.lot-tido.com
	Created: 4/2/2019 11:18:27 PM
*	Update Date:	05-OCT-2020
*	Description: 
*
*/
#include "reloj.h"
#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "Default_RGB.h"
#include "Lot.TiDo_Blynk_RGB.h"
char cadenas2[256];
WiFiUDP Udp;
unsigned int localPort = 8888;
// NTP time is in the first 48 bytes of message
const int NTP_PACKET_SIZE = 48;

byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets
void sendNTPpacket(IPAddress &address);
reloj_calendario::reloj_calendario(int _timeZone) {
	timeZone1 = _timeZone;
}
bool reloj_calendario::init() {
	Udp.begin(localPort);
	setSyncProvider(getNtpTime);
	setSyncInterval(300);
}
time_t reloj_calendario::getNtpTime() {
	IPAddress ntpServerIP; // NTP server's ip address

	while (Udp.parsePacket() > 0) ; // discard any previously received packets
	Serial.println("Transmit NTP Request");
	// get a random server from the pool
	WiFi.hostByName(ntpServerName, ntpServerIP);
	Serial.print(ntpServerName);
	Serial.print(": ");
	Serial.println(ntpServerIP);
	sendNTPpacket(ntpServerIP);
	uint32_t beginWait = millis();
	while (millis() - beginWait < 1500) {
		int size = Udp.parsePacket();
		if (size >= NTP_PACKET_SIZE) {
			Serial.println("Receive NTP Response");
			Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
			unsigned long secsSince1900;
			// convert four bytes starting at location 40 to a long integer
			secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
			secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
			secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
			secsSince1900 |= (unsigned long)packetBuffer[43];
			return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
		}
	}
	Serial.println("No NTP Response :-(");
	return 0; // return 0 if unable to get the time
}
int reloj_calendario::hora(){
	return hour();
}
int reloj_calendario::minutos() {
	return minute();
}
int reloj_calendario::segundos() {
	return second();
}
int reloj_calendario::dia(){
	return day();
}
int reloj_calendario::dia_semana() {
	return weekday();
}
int reloj_calendario::mes(){
	return month();
}
int reloj_calendario::anio(){
	return year();
}
bool reloj_calendario::status() {
	sprintf(cadenas2, "estado: %d\n", estado);
	terminal(cadenas2);
	if( estado ) {
		if( hora() != horaAlarm ) return false;
		if( minute() != minutoAlarm )return false;
		if( !diaSemanaAlarm[weekday()-1] ) return false;
		return true;
	}
	return false;
}
void reloj_calendario::enable(){
	estado = true;
}
bool reloj_calendario::enableButton() {
	return estado;
}
void reloj_calendario::disable() {
	estado = false;
}
void reloj_calendario::setHora(int _hora, int _minutos){
	horaAlarm = _hora;
	minutoAlarm = _minutos;
}
void reloj_calendario::setWeekDay(int week[7]) {
	int aux=week[6];
	for( int i = 6; i > 0; i-- ) {
		week[i] = week[i - 1];
	}
	week[0] = aux;
	for( int i = 0; i < 7; i++ ) {
		diaSemanaAlarm[i] = week[i];
	}
}
void reloj_calendario::setFecha(int _dia, int _dia_semana,
								int _mes, int _anio) {
	diaAlarm = _dia;
//	diaSemanaAlarm = _dia_semana;
	mesAlarm = _mes;
	anioAlarm = _anio;
}
void reloj_calendario::getFecha(char cadena[11]){
	char aux[10];
	char aux1[10];
	char aux2[10];
	if( diaAlarm < 10 ) sprintf(aux, "0%d",diaAlarm);
	else sprintf(aux, "%d/",diaAlarm);
	if( mesAlarm < 10 ) sprintf(aux1, "0%d", mesAlarm);
	else sprintf(aux1, "%d/",mesAlarm);
	if( anioAlarm < 10 )        sprintf(aux2, "000%d", anioAlarm);
	else if( anioAlarm < 100 )  sprintf(aux2, "00%d", anioAlarm);
	else if( anioAlarm < 1000 ) sprintf(aux2, "0%d", anioAlarm);
	sprintf(cadena, "%s/%s/%s", aux,aux1,aux2);
}
void reloj_calendario::getHora(char cadena[11]) {
	char aux[10];
	char aux1[10];
	if( horaAlarm < 10 ) sprintf(aux, "0%d",horaAlarm );
	else sprintf(aux, "%d",horaAlarm );
	if( minutoAlarm < 10 ) sprintf(aux, "0%d",minutoAlarm );
	else sprintf(aux, "%d",minutoAlarm );
	sprintf(cadena, "%s:%s", aux,aux1);

}
void reloj_calendario::setName(char _name[256]) {
	strcpy(name, _name);
}
void reloj_calendario::getName(char _name[256]) {
	strcpy(_name, name);
}
void sendNTPpacket(IPAddress &address){
	// set all bytes in the buffer to 0
	memset(packetBuffer, 0, NTP_PACKET_SIZE);
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	packetBuffer[0] = 0b11100011;   // LI, Version, Mode
	packetBuffer[1] = 0;     // Stratum, or type of clock
	packetBuffer[2] = 6;     // Polling Interval
	packetBuffer[3] = 0xEC;  // Peer Clock Precision
							 // 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer[12] = 49;
	packetBuffer[13] = 0x4E;
	packetBuffer[14] = 49;
	packetBuffer[15] = 52;
	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp:
	Udp.beginPacket(address, 123); //NTP requests are to port 123
	Udp.write(packetBuffer, NTP_PACKET_SIZE);
	Udp.endPacket();
}
bool noBlockDelay(unsigned long *time, int delayMillis) {
	if( millis() > *time ) {
		*time = millis() + delayMillis;
		return true;
	}
	return false;
}
bool noBlockDelayMicros(unsigned long *time, int delayMicros) {
	if( micros() > *time ) {
		*time = micros() + delayMicros;
		return true;
	}
	return false;
}
bool noBlockDelayFuncion(unsigned long *time, int delayMillis, 
						 void (*funcion)()) {
	if( millis() > *time ) {
		*time = millis() + delayMillis;
		funcion();
		return true;
	}
	return false;
}