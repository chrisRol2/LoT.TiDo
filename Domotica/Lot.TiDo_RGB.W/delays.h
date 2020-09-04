// delays.h

#ifndef _DELAYS_h
#define _DELAYS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif


void noblock_delay(void *funcion(), long *delay_millis, long delay_accum);
