// blynk_bt.h

#ifndef _BLYNK_BT_h
#define _BLYNK_BT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

class Blynk_bt {
private:
	char auth[];
public:
	Blynk_bt(char _auth[]);
	void run();
	void init();
};