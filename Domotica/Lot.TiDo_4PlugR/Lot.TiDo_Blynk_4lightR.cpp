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
void offline_funcions(){
	interrupcion_0();
	delay(10);
	interrupcion_1();
	delay(10);
}

char api_connect(char token[]) {
	Blynk.begin(token, NULL, NULL);
	Blynk.syncVirtual(V1,V2);
	return Blynk.connected();
}

bool isTokenValid() {
	return !Blynk.isTokenInvalid();

}

void api_Run() {
	Blynk.run();
}

bool connected() {

	return Blynk.connected();
}

//----------------------- BLYNK CONECT ------------------------------------
//-------------------------------------------------------------------------


BLYNK_WRITE(V1)
{
	int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
	if (pinValue == 1) {
		estado_0 = true;
	}
	else {
		estado_0 = false;
	}	
	digitalWrite(light_0, !estado_0);
}
BLYNK_WRITE(V2)
{

	int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
	if (pinValue == 1) {
		estado_1 = true;
	}
	else {
		estado_1 = false;
	}
	digitalWrite(light_1, !estado_1);
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
	else if (String("reset") == input_terminal) {
		ESP.restart();
	}
	else {

		// Send it back
		
	}

	// Ensure everything is sent
	terminal.flush();
}

//----------------------- BLYNK VIRTUAL PIN  ------------------------------
//-------------------------------------------------------------------------
//------------------------- INTERRUPCIONES --------------------------------
int off_all = 0;
int double_clic = 0, double_cont;
void interrupcion_0() {
	//terminal.print("Interrupcion 0");
	light_0_EstadoActual = digitalRead(light_switch_0);
	// compare the light_0_EstadoActual to its previous state
	if ((light_0_EstadoActual != light_0_EstadoAnterior)) {
		if (light_0_EstadoActual == HIGH) {
			estado_0 = !estado_0;
			digitalWrite(light_0, !estado_0);
			Blynk.virtualWrite(V1, estado_0);	
			off_all = 0;
		}
	}

	if (light_0_EstadoActual == HIGH) {
		off_all++;
		delay(1);
	}
	else if (off_all >= 40) {

		estado_0 = false;
		digitalWrite(light_0, !estado_0);
		Blynk.virtualWrite(V1, estado_0);

		estado_1 = false;
		digitalWrite(light_1, !estado_1);
		Blynk.virtualWrite(V2, estado_1);

		terminal.print("OFF_ALL 0: ");
		terminal.println(off_all);
		terminal.flush();
		off_all = 0;

	}



	// save the current state as the last state, for next time through the loop
	light_0_EstadoAnterior = light_0_EstadoActual;

}

void interrupcion_1() {
	//terminal.print("Interrupcion 1");
	
	light_1_EstadoActual = digitalRead(light_switch_1);

	// compare the light_0_EstadoActual to its previous state
	if ((light_1_EstadoActual != light_1_EstadoAnterior)) {
		if (light_1_EstadoActual == HIGH) {
			estado_1 = !estado_1;
			digitalWrite(light_1, !estado_1);
			Blynk.virtualWrite(V2, estado_1);
			off_all = 0;
			double_clic++;
		}
	}
	if (double_clic == 2){
		double_clic = 0;
		
		estado_0 = true;
		digitalWrite(light_0, !estado_0);
		Blynk.virtualWrite(V1, estado_0);

		estado_1 = true;
		digitalWrite(light_1, !estado_1);
		Blynk.virtualWrite(V2, estado_1);


		terminal.print("double: ");
		terminal.println(double_cont);
		terminal.flush();
		double_cont = 0;
	}
	if (light_1_EstadoActual == HIGH) {
		off_all++;
		delay(1);
	}
	else if(off_all >= 40) {

		estado_0 = false;
		digitalWrite(light_0, !estado_0);
		Blynk.virtualWrite(V1, estado_0);

		estado_1 = false;
		digitalWrite(light_1, !estado_1);
		Blynk.virtualWrite(V2, estado_1);

		terminal.print("OFF_ALL: ");
		terminal.println(off_all);
		terminal.flush();
		off_all = 0;
		double_cont = double_clic = 0;

	}
	else {
		double_cont++;
		delay(1);
		if (double_cont >= 20) {
			double_cont = double_clic = 0;
			
		}
	}
	// save the current state as the last state, for next time through the loop
	light_1_EstadoAnterior = light_1_EstadoActual;
}