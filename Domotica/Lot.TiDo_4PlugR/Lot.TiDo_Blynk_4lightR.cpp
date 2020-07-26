// 
// 
// 

#include "Lot.TiDo_Blynk_4lightR.h"
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


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

/*
BLYNK_WRITE(V1)
{
	int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

	// process received value
}
BLYNK_WRITE(V2)
{
	int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

	// process received value
}
*/