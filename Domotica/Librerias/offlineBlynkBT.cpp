/*
 * offlineBlynk.BT.cpp
 *
 * Created: 4/2/2019 11:18:27 PM
 * Author:	Christoher Roldan Sanchez
 * Email:	Christopher_rol@hotmail.es
 */

#include "offlineBlynkBT.h"


#define BLYNK_USE_DIRECT_CONNECT
#define BLYNK_PRINT Serial1

char auth[] = "7a312d29e2d24f6b80f71b8a1a16cce4";

void test() {
	
	Blynk.run();
}