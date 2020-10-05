/*
*	File:	LoT.Tido_RGB.cpp
*	Author:	Christopher Roldan Sanchez
*	Mail:	Christopher_Rol@hotmail.es
*   Web:    https://www.lot-tido.com
*	Update Date:	05-OCT-2020
*	Description: Class for general operation of lights (RGB, WHITE, 220VAC)
*
*/
#include "rgb_colors_Hue.h"
#include "LoT.Tido_RGB.h"
#include "Lot.TiDo_Blynk_RGB.h"
#include "reloj.h"
#include "Default_RGB.h"

reloj_calendario RTClock(-3);

bool RBG_STRIP::compare(int color[3], int color2[3]) {
	for( int i = 0; i < 3; i++ ) {
		if( color[i] != color2[i] )return false;
	}
	return true;
}
void RBG_STRIP::set(int red, int green, int blue, int depth) {
	depth = pow(2, depth) - 1;

	analogWrite(red_pin,
				map(red, 0, depth, 0, brightness));
	analogWrite(green_pin,
				map(green, 0, depth, 0, brightness));
	analogWrite(blue_pin, 
				map(blue, 0, depth, 0, brightness));
}
void RBG_STRIP::set(int color[3], int depth) {
	depth = pow(2, depth) - 1;
	static int pin[3] = { red_pin, green_pin, blue_pin };

	for( int i = 0; i < 3; i++ ) {
		analogWrite(pin[i],
					map(color[i], 0, depth, 0, brightness));
	}
	
}
void RBG_STRIP::change(int _status) {
	status = _status;
	refresh();
}
void RBG_STRIP::RGB(int red, int green, int blue) {
	RED_VALUE = red;
	GREEN_VALUE = green;
	BLUE_VALUE = blue;
	refresh();
}
void RBG_STRIP::RGB(int color[3]) {
	RED_VALUE = color[0];
	GREEN_VALUE = color[1];
	BLUE_VALUE = color[2];
	refresh();
}
void RBG_STRIP::on() {
	status = true;
	refresh();
}
void RBG_STRIP::off() {
	status = false;
	refresh();
}
void RBG_STRIP::toggle() {
	status = !status;
	refresh();
}
void RBG_STRIP::setBrightness(int _brightness) {
	brightness = _brightness;
	refresh();
}
void RBG_STRIP::getColor(int rgb[3]) {
	rgb[0] = RED_VALUE;
	rgb[1] = GREEN_VALUE;
	rgb[2] = BLUE_VALUE;
}
void RBG_STRIP::toVec(int red, int green, int blue, int vec[3]) {
	vec[0] = red; vec[1] = green; vec[2] = blue;
}
void RBG_STRIP::mode(int _mode_rgb) {
	mode_rgb = _mode_rgb;
}
void RBG_STRIP::setSpeed(int _speed) {
	speed = _speed;
}
void RBG_STRIP::random_color() {
	set(colores[random(0, 24)], 8);
}
void RBG_STRIP::fade(int color[50][3], int cantidad) {
	static int dest = 0;
	if( firstloop ) {
		firstloop = false;
		modes_cont = 0;
		destCont = 0;
		for( int i = 0; i < 3; i++ )colorFuncions[i] = 0;
	}
	if( !compare(color[dest], colorFuncions) ) {
		for( int i = 0; i < 3; i++ ) {
			if( colorFuncions[i] < color[dest][i] )
				colorFuncions[i]++;
			else if( colorFuncions[i] > color[dest][i] )
				colorFuncions[i]--;
		}
	} else {
		destCont++;
		dest = destCont % cantidad;
	}
	set(colorFuncions, 8);
}
void RBG_STRIP::flash() {
	static bool  modes_toggle = false;
	if( modes_toggle ) {
		set(RED_VALUE, GREEN_VALUE, BLUE_VALUE, 8);
		modes_toggle = false;
	}
	else {
		set(0, 0, 0, 1); modes_toggle = true;
	}
}
void RBG_STRIP::pulse() {
	if( firstloop ) {
		firstloop = false; modes_cont = 0;
	}
	modes_cont += 0.005;
	brightness = (int) (509 * sin(modes_cont) + 514);
	set(RED_VALUE, GREEN_VALUE, BLUE_VALUE, 8);
}
void RBG_STRIP::refresh() {
	static unsigned long delayModespeed = 0;
	if( mode_rgb != previus_mode ) {
		firstloop = true;
		previus_mode = mode_rgb;
		delayModespeed = millis() + speed;
	}
	if( status == 1 ) {
		switch( mode_rgb ) {
			case STATIC:
				set(RED_VALUE, GREEN_VALUE, BLUE_VALUE, 8);
				break;
			case FADE:
				if( noBlockDelayMicros(&delayModespeed, (speed * 1000) / 5) )
					fade(colores, 25);
				break;
			case FLASH:
				if( noBlockDelay(&delayModespeed, speed) )
					flash();
				break;
			case RANDOM:
				if( noBlockDelay(&delayModespeed, speed) )
					random_color();
				break;
			case PULSE:
				if( noBlockDelayMicros(&delayModespeed, (speed * 1000) / 5) )
					pulse();
				break;
			default:defaultMode();
		}
	}
	else if( status == -1 ) {

	}
	else{
		set(0, 0, 0, 8);
	}
}
void RBG_STRIP::defaultMode() {

}