// Lot.TiDo_CONNECTWiFi.h

#ifndef _LOT.TIDO_CONNECTWIFI_h
#define _LOT.TIDO_CONNECTWIFI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif



//define your default values here, if there are different values in config.json, they are overwritten.



void saveConfigCallback();
void setupSpiffs();
void LotSetup();
void lotLoop();
void wifi_data(char nameAP[]);
void get_key(char key_blynk[]);