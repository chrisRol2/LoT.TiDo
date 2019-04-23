/*
 Name:		NodeMCU.ino
 Created:	15/04/2019 13:20:45
 Author:	chris
*/

#include "estados_esp8266.h"
#include "WiFi_esp8266.h"
config IO(4);
estados DOIT;



void setup() {
	IO.init();
	DOIT.config();
	
}


void loop() {
	DOIT.permanente();
}
