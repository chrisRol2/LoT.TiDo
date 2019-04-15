/*
 * interrupciones.cpp
 *
 * Created: 4/2/2019 11:18:27 PM
 * Author:	Christoher Roldan Sanchez
 * Email:	Christopher_rol@hotmail.es
 */

#include "interrupciones.h"
#include "pinesIO.h"

void i2c_interrupcion(void){
	
}
void MQ_2_interrupcion(void){

}
void pir_interrupcion(void){
	
}
void piezo_pip(unsigned char veces, unsigned char delay_pip) {
	for (int i = 0; i < veces ; i++) {
		digitalWrite(pin_PIEZO, 1);
		delayMicroseconds(delay_pip * 1000);
		digitalWrite(pin_PIEZO, 0);
		delayMicroseconds(delay_pip * 1000);
	}
}
void errores(unsigned char error_tipo = 0) {
	Serial.print("ERROR TIPO: "); Serial.println(error_tipo);
	switch (error_tipo) {
		case 0:
		piezo_pip(2, 100);
		break;
		case 1:
		break;
		case 2:
		piezo_pip(2, 250);
		break;
		default:
		break;
	}
}
void retraso ( unsigned long tiempo, void funcion(), unsigned long &t) {

	if (t < millis()) {
		t = tiempo + millis();
		funcion();
	}
	return;
}
bool retraso_BOOL ( unsigned long tiempo, void funcion(), unsigned  char &t) {
	if (t < millis()) {
		t = tiempo + millis();
		funcion();
		return true;
	}
	return false;
}