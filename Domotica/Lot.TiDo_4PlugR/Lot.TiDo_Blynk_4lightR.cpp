// 
// 
// 

#include "Lot.TiDo_Blynk_4lightR.h"
#include "Defaults_2LightR.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Arduino.h>
#define BLYNK_PRINT Serial
void interrupcion_0();
void interrupcion_1();

bool light_0_EstadoActual = 0;
bool light_0_EstadoAnterior = 0;

bool light_1_EstadoActual = 0;
bool light_1_EstadoAnterior = 0;

bool estado_0 = true;
bool estado_1 = true;


WidgetTerminal terminal(V3);
//-------------------------------------------------------------------------
//----------------------- BLYNK CONECT ------------------------------------
void init_interrupciones(){
	//attachInterrupt(digitalPinToInterrupt(light_switch_0), interrupcion_0, FALLING);
	//attachInterrupt(digitalPinToInterrupt(light_switch_1), interrupcion_1, FALLING);
	attachInterrupt(digitalPinToInterrupt(4), interrupcion_0, HIGH);
	attachInterrupt(digitalPinToInterrupt(5), interrupcion_1, HIGH);
	
}

char api_connect(char token[]) {
	Blynk.begin(token, NULL, NULL);
	Serial.println("Blynk inicio");
	return Blynk.connected();
}

bool isTokenValid() {
	return !Blynk.isTokenInvalid();

}

void api_Run() {
	Blynk.run();
}

//----------------------- BLYNK CONECT ------------------------------------
//-------------------------------------------------------------------------


BLYNK_WRITE(V1)
{
	int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
	if (pinValue == 1) {
		estado_0 = false;
	}
	else {
		estado_0 = true;
	}	
	digitalWrite(light_0, estado_0);
	terminal.print("Luz 0: "); terminal.println(estado_0);
	terminal.flush();
	Serial.print("Luz 0: "); Serial.println(estado_0);
}
BLYNK_WRITE(V2)
{

	int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
	if (pinValue == 1) {
		estado_1 = false;
	}
	else {
		estado_1 = true;
	}
	digitalWrite(light_1, estado_1);
	terminal.print("Luz 1: "); terminal.println(estado_1);
	terminal.flush();
	Serial.print("Luz 1: "); Serial.println(estado_1);
}

BLYNK_WRITE(V3)
{
	String input_terminal = param.asStr();
	// if you type "Marco" into Terminal Widget - it will respond: "Polo:"
	if (String("Marco") == input_terminal) {
		terminal.println("You said: 'Marco'");
		terminal.println("I said: 'Polo'");
	}
	else if (String("cls") == input_terminal) {
		terminal.clear();
	}
	else {

		// Send it back
		terminal.print("You said:");
		terminal.write(param.getBuffer(), param.getLength());
		terminal.println();
	}

	// Ensure everything is sent
	terminal.flush();
}

//----------------------- BLYNK VIRTUAL PIN  ------------------------------
//-------------------------------------------------------------------------
//------------------------- INTERRUPCIONES --------------------------------

void interrupcion_0() {
	//terminal.print("Interrupcion 0");

}
void interrupcion_1() {
	//terminal.print("Interrupcion 1");
}