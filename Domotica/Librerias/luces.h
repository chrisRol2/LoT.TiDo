/*
*	File:	luces.h
*	Author : Christopher Roldan Sanchez
*	Mail : Christopher_Rol@hotmail.es
*	Date:
*	Description :
*
*/

#ifndef _LUCES_h
#define _LUCES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

#define TACTIL	 0
#define PULL_UP	 1
#define HIGH_IMP 0

class lampara {
private:
	unsigned int rojo = 0;
	unsigned int verde = 0;
	unsigned int azul = 0;
	unsigned int porcentaje = 100;
	unsigned int pin;
	unsigned int pinR, pinG, pinB;
	bool status = false;
	bool isRGB = false;
	bool isAnalog = true;
	bool auto_OFF = true;
	unsigned long retraso_off = 60000;
	void refresh();
public:

	lampara(bool _isRGB, bool _isAnalog, unsigned int _pin) : isRGB(_isRGB),
		isAnalog(_isAnalog), pin(_pin) {}

	lampara(bool _isRGB, unsigned int _pin_R, unsigned int _pin_G,
		unsigned int _pin_B) : isRGB(_isRGB), pinR(_pin_R), 
		pinG(_pin_G), pinB(_pin_B) {}
	void on();
	void off();
	void set(unsigned int red, unsigned int green, unsigned int blue);
	void set(unsigned int brillo_porcentaje);
	void toggle();
	void autoOFF();
	void setAutoOFF(bool _auto_OFF, unsigned long _retraso_off);

};

class LUZ_blynk{
private:
	char pin_hardware;
	char pin_Blynk;
	char estado;
	char pin_button;

	bool readButton();

public:
	LUZ_blynk(char _pin_hardware, char _pin_Blynk, char _pin_button) : pin_hardware(_pin_hardware),
		pin_Blynk(_pin_Blynk), pin_button(_pin_button) {}
	void init(bool estado_inicio, int tipo_boton);
	bool refresh();
	void on();
	void off();
	void toggle();
	void run();

};
