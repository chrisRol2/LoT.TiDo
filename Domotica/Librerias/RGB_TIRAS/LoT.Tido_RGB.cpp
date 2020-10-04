// 
// 
// 
#include "rgb_colors_Hue.h"
#include "LoT.Tido_RGB.h"

#include "Lot.TiDo_Blynk_RGB.h"
bool RBG_STRIP::compare(int color[3],int color2[3]) {
	for( int i = 0; i < 3; i++ ) {
		if( color[i] != color2[i] )return false;
	}
	return true;
}
void RBG_STRIP::set(int red, int green, int blue,int depth) {
	depth = pow(2, depth) - 1;
	volatile int redB = map(red, 0, depth, 0, brightness);
	volatile int greenB = map(green, 0, depth, 0, brightness);
	volatile int blueB = map(blue, 0, depth, 0, brightness);

	analogWrite(red_pin, redB);
	analogWrite(green_pin, greenB);
	analogWrite(blue_pin, blueB);
}
void RBG_STRIP::set( int color[3],int depth) {
	depth = pow(2, depth) - 1;
	volatile int redB = map(color[0], 0, depth, 0, brightness);
	volatile int greenB = map(color[1], 0, depth, 0, brightness);
	volatile int blueB = map(color[2], 0, depth, 0, brightness);

	analogWrite(red_pin, redB);
	analogWrite(green_pin, greenB);
	analogWrite(blue_pin, blueB);
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
	volatile int seleccion = random(0, 24);
	set(colores[seleccion], 8);
}
void RBG_STRIP::fade(int color[50][3],int cantidad) {
	static int dest = 0;
	if( !compare(color[dest], colorFuncions) ) {
		for( int i = 0; i < 3; i++ ) {
			if( colorFuncions[i] < color[dest][i] )colorFuncions[i]++;
			else if( colorFuncions[i] > color[dest][i] )colorFuncions[i]--;
		}
	}
	else {
		destCont++;
		dest = destCont % cantidad;
		sprintf(cadena, "Estado: %d", dest);
		terminal(cadena);
	}
	set(colorFuncions, 8);
}
void RBG_STRIP::refresh() {
	static float modes_cont;
	static bool firstloop = true;
	static bool  modes_toggle = false;
	static int previus_mode = 0;
	static unsigned long delayModespeed = 0;
	
	if( mode_rgb != previus_mode ) {
		firstloop = true;
		previus_mode = mode_rgb;
		delayModespeed = millis() + speed;
	}

	if( status ) {
		switch( mode_rgb ) {
			case 1:
				set(RED_VALUE, GREEN_VALUE, BLUE_VALUE, 8);
				break;
			case 2: // fade
				if( firstloop ) {
					firstloop = false;
					modes_cont = 0;
					destCont = 0;
					for( int i = 0; i < 3; i++ )colorFuncions[i] = 0;
				}
				if( micros() > delayModespeed ) {
					delayModespeed = micros() + (speed * 1000) / 5;
					fade(colores,25);
				}
				break;
			case 3: // flash				
				if( millis() > delayModespeed ) {
					delayModespeed = millis() + speed;
					if( modes_toggle ) {
						set(RED_VALUE, GREEN_VALUE, BLUE_VALUE, 8);
						modes_toggle = false;
					}
					else {
						set(0, 0, 0, 1);
						modes_toggle = true;
					}
				}
				break;
			case 4: // random				
				if( millis() > delayModespeed ) {
					random_color();
					delayModespeed = millis() + speed;
				}
				break;
			case 5: // pulse
				if( firstloop ) {
					firstloop = false;
					modes_cont = 0;
				}
				if( micros() > delayModespeed ) {
					delayModespeed = micros() + (speed*1000) / 5;
					modes_cont+= 0.005;
					brightness = (int)(509 * sin(modes_cont ) + 514);
					set(RED_VALUE, GREEN_VALUE, BLUE_VALUE, 8);
				}
				break;
			default:
				break;
		}
	}
	else {
		set(0, 0, 0, 8);
	}
}
void RBG_STRIP::test() {	

}