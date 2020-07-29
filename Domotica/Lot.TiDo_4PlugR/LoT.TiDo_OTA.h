// LoT.TiDo_OTA.h

#ifndef _LOT.TIDO_OTA_h
#define _LOT.TIDO_OTA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

void OTA_SETUP(char Host_name[], char Host_pw[]);
void OTA_RUN();
