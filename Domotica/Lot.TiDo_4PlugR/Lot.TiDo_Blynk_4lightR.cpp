// 
// 
// 

#include "Lot.TiDo_Blynk_4lightR.h"
#include "Defaults_2LightR.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial


bool light_0_EstadoActual = 0;
bool light_0_EstadoAnterior = 0;

bool light_1_EstadoActual = 0;
bool light_1_EstadoAnterior = 0;

//-------------------------------------------------------------------------
//----------------------- BLYNK CONECT ------------------------------------


char api_connect(char token[]) {
	Blynk.begin(token, NULL, NULL);
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
	Blynk.virtualWrite(V1,light_0_EstadoActual);

	// process received value
}
BLYNK_WRITE(V2)
{
	int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
	

	if ((digitalRead(light_switch_1 && light_1_EstadoActual != light_1_EstadoAnterior))) {
		light_1_EstadoActual != light_1_EstadoActual;
		light_1_EstadoAnterior = light_1_EstadoActual;
		Blynk.virtualWrite(V1,light_1_EstadoActual);
	}
	Blynk.virtualWrite(V2, light_0_EstadoActual);
	digitalWrite(light_1, light_1_EstadoActual);
}
