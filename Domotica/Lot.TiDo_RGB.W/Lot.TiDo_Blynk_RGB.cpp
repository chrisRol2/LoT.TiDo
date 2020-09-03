
#include "Default_RGB.h"
//
#include "Lot.TiDo_Blynk_RGB.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Arduino.h>
#include "LoT.Tido_RGB.h"


//#include "rgb_colors_Hue.h"

#define BLYNK_PRINT Serial

RBG_STRIP desktop(RED_PIN, GREEN_PIN, BLUE_PIN);

WidgetTerminal terminal(V3);
BLYNK_WRITE(V1) {
	int data = param.asInt();
	if (data){
		terminal.println("conecto");
	}
	else {
		terminal.println("no conecto");
	}
	terminal.flush();
}
void terminal_println(char cosa[]) {
	terminal.print(cosa);
	terminal.flush();
}

char api_connect(char token[]) {
	Blynk.begin(token, NULL, NULL);
	Blynk.syncAll();
	
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
}

BLYNK_WRITE(V29) {

	desktop.change(param.asInt());
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
