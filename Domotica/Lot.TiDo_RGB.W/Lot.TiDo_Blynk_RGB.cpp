
#include "Default_RGB.h"
#include "rgb_colors_Hue.h"
#include "Lot.TiDo_Blynk_RGB.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Arduino.h>
#include "LoT.Tido_RGB.h"



#define BLYNK_PRINT Serial

RBG_STRIP desktop(RED_PIN, GREEN_PIN, BLUE_PIN);

char api_connect(char token[]) {
	Blynk.begin(token, NULL, NULL);
	Blynk.syncAll();
	return Blynk.connected();
}

bool isTokenValid() {
	return !Blynk.isTokenInvalid();

}

void api_Run() {
	Blynk.run();
	
}

void init_interrupciones() {

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

	desktop.mode(param.asInt());

}
