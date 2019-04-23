// 
// 
// 

#include "luces.h"


 void lampara::on(){
	 status = true;
	 if (isRGB) {
		 analogWrite(pinR, (porcentaje * rojo) / 100);
		 analogWrite(pinG, (porcentaje * verde) / 100);
		 analogWrite(pinB, (porcentaje * azul) / 100);
	 }
	 else {
		 if (isAnalog)analogWrite(pin, (porcentaje * 255) / 100);
		 else digitalWrite(pin, 1);
	 }
 }
 void lampara::off(){
	 status = false;
	 if (isRGB) {
		 analogWrite(pinR, 0);
		 analogWrite(pinG, 0);
		 analogWrite(pinB, 0);
	 }
	 else {
		 if (isAnalog)digitalWrite(pin, 0);
		 else analogWrite(pin, 0);
	 }
 }
 void lampara::set(unsigned int red, unsigned int green, unsigned int blue){
	 rojo = red;
	 verde = green;
	 azul = blue;
	 refresh();
 }
void lampara::set(unsigned int brillo_porcentaje) {
	porcentaje = brillo_porcentaje;
	refresh();

}
 void lampara::toggle(){
	 status != status;
	 refresh();
 }
//  void lampara::autoOFF(){  // esta funcion requiere de sensor pir
// 	 status = false;
//  }
void lampara::setAutoOFF(bool _auto_OFF, unsigned long _retraso_off){
	auto_OFF = _auto_OFF;
	retraso_off = _retraso_off;
}
void lampara::refresh(){
		if (status)on();
		else off();
}

