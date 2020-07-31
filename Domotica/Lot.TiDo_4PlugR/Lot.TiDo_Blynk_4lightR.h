// Lot.TiDo_Blynk_4lightR.h

#ifndef _LOT.TIDO_BLYNK_4LIGHTR_h
#define _LOT.TIDO_BLYNK_4LIGHTR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif


char api_connect(char token[]);
void api_Run();
bool isTokenValid();
void init_interrupciones();