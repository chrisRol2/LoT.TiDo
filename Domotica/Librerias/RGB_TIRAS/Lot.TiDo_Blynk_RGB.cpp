/*
*	File:
*	Author:	Christopher Roldan Sanchez
*	Mail:	Christopher_Rol@hotmail.es
*   Web:    https://www.lot-tido.com
*	Created:
*	Update Date:
*	Description:
*/
#include "Default_RGB.h"
#include "Lot.TiDo_Blynk_RGB.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Arduino.h>
#include "LoT.Tido_RGB.h"
#define BLYNK_MAX_SENDBYTES 256
#define BLYNK_PRINT Serial
char cadenas[256];
RBG_STRIP desktop(RED_PIN, GREEN_PIN, BLUE_PIN);
WidgetBridge Light2(V1);

void terminal(char printeable[]) {
	Light2.virtualWrite(V3, printeable);
}
void terminal(String printeable) {
	Light2.virtualWrite(V3, printeable);
}
void notify(char cadena[128]) {
	Blynk.notify(cadena);
}
void refreshBlynk() {
	Blynk.syncVirtual(V34);
}
char api_connect(char token[],char token2[]) {
	Blynk.begin(token, NULL, NULL);
	Light2.setAuthToken(token2);	
	//Blynk.syncAll();
	Blynk.syncVirtual(V19,V14,V34,V30,V5,V20,V21,V22);
	desktop.init();
	return Blynk.connected();
}
bool connected() {
	return Blynk.connected();
}
bool isTokenValid() {
	return !Blynk.isTokenInvalid();
}
void api_Run() {
	Blynk.run();
}
void offline_funcions() {
	desktop.refresh();
}
BLYNK_WRITE(V19) {
	desktop.RGB(param[0].asInt(),param[1].asInt(),param[2].asInt());
	Blynk.syncVirtual(V34);
}
BLYNK_WRITE(V29) {
	desktop.change(param.asInt());
	Blynk.syncVirtual(V34);
}
BLYNK_WRITE(V14) {
	desktop.setBrightness(param.asInt());
}
BLYNK_WRITE(V34) {
	volatile int modes = param.asInt();
	Blynk.syncVirtual(V14);
	
	switch( modes ) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			Blynk.setProperty(V30, "min", 1);
			Blynk.setProperty(V30, "max", 250);
			break;
		case 4: 
			Blynk.setProperty(V30, "min", 1);
			Blynk.setProperty(V30, "max", 2000);
			break;
		case 5:
			Blynk.setProperty(V30, "min", 2);
			Blynk.setProperty(V30, "max", 50);
			break;
		default:
			break;
	}
	desktop.mode(modes);
}
BLYNK_WRITE(V30) {
	desktop.setSpeed(param.asInt());
}
BLYNK_WRITE(V5) {
	volatile int value = param.asInt();
	desktop.change(value);
	Blynk.virtualWrite(V29, value);
	Light2.virtualWrite(V4, value);
	Light2.virtualWrite(V2, value);
}
BLYNK_WRITE(V20) {
    TimeInputParam t(param);
	if( t.isStartSunrise() ) {
		terminal("Start at sunrise");
	}
	else if( t.isStartSunset() ) {
		terminal("Start at sunset");
	}


    // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
	int weekday[7];
    for (int i = 1; i <= 7; i++) {
		weekday[i - 1] = t.isWeekdaySelected(i);
        if (t.isWeekdaySelected(i)) {
            terminal(String("Day ") + i + " is selected");
        }
    }
    terminal("\n");
	setDespertador(t.getStartHour(),
				   t.getStartMinute(), 
				   weekday);
}
BLYNK_WRITE(V21) {
	String textIn = param.asStr();
	setNombre(textIn);
}
BLYNK_WRITE(V22) {
	setStateDespertador(param.asInt());
	Blynk.syncVirtual(V34);
	
}
