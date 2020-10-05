/*
*	File:	Lot.TiDo_CONNECTWiFi.h
*	Author:	Christopher Roldán Sánchez
*	Mail:	Christopher_Rol@hotmail.es
*   Web:    https://www.lot-tido.com
*	Created:
*	Update Date:
*	Description: 
*/

#ifndef _LOT.TIDO_CONNECTWIFI_h
#define _LOT.TIDO_CONNECTWIFI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif


#define RECONNECTION_TIME 3000

//define your default values here, if there are different values in config.json, they are overwritten.

void wifi_data(char nameAP[], char nameSIS[], char passwordDEF[]);
void get_key(char key_blynk[]);
void get_key2(char key_blynk[]);
void setupSpiffs();
void WiFiManager_setup();
void clear_Data();
bool connected_wifi();