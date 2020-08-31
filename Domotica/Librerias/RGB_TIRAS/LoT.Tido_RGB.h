// LoT.h

#ifndef _LoT.Tido_RGB_h
#define _LoT.Tido_RGB_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

class RBG_STRIP {
private:
	int red_pin;
	int green_pin;
	int blue_pin;

	int RED_VALUE;
	int GREEN_VALUE;
	int BLUE_VALUE;

	int brightness = 1023;

	bool status;

	int mode_rgb;

	void set(int red, int green, int blue);

	//modos

	void random_color();
	
public:
	RBG_STRIP(int _red_pin, int _green_pin, int _blue_pin):
		red_pin(_red_pin), green_pin(_green_pin), blue_pin(_blue_pin) {
	}
	void RGB(int red, int green, int blue);
	void RGB(int color[3]);
	void on();
	void off();
	void change(int _status);
	void toggle();
	void setBrightness(int _brightness);
	void getColor(int rgb[3]);
	void refresh();
	void mode(int _mode_rgb);
};

