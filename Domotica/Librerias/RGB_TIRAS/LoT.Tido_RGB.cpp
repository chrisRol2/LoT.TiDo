// 
// 
// 

#include "LoT.Tido_RGB.h"
#include "rgb_colors_Hue.h"

void RBG_STRIP::set(int red, int green, int blue) {
	analogWrite(red_pin, red);
	analogWrite(green_pin, green);
	analogWrite(blue_pin, blue);
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

void RBG_STRIP::refresh() {
	volatile int redB = map(RED_VALUE,0,1023,0,brightness);
	volatile int greenB = map(GREEN_VALUE, 0, 1023, 0, brightness);
	volatile int blueB = map(BLUE_VALUE, 0, 1023, 0, brightness);

	if( status ) {
		switch( mode_rgb ) {
			case 1:
				set(redB, greenB, blueB);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				random_color();
				break;
			case 5:
				break;
			default:
				break;
		}
		
	}
	else {
		set(0, 0, 0);
	}
}

void RBG_STRIP::mode(int _mode_rgb) {

	mode_rgb = _mode_rgb;

}

void RBG_STRIP::random_color() {

	volatile int seleccion = random(0, 24);
	RGB(colores[seleccion]);
	return;
}