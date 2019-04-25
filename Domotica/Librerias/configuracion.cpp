/*
 * configuraciones.cpp
 *
 * Created: 4/2/2019 11:18:27 PM
 * Author:	Christoher Roldan Sanchez
 * Email:	Christopher_rol@hotmail.es
 */

#include "configuracion.h"
#include "interrupciones.h"
#include "pinesIO.h"
#include <Wire.h>
#include <math.h>
void iniciar_declarar::serial() {
	Serial.begin(Serial_Baud);
	return;
}
void iniciar_declarar::bluetooth() {
	Serial.println("Se inicia Bluetooth");
	const char BT_AUDIO[7] = { pin_BT_VOL_UP, pin_BT_VOL_DOWN, pin_BT_NEXT,
				pin_BT_PREV, pin_BT_PPCALL, pin_BT_MUTE, pin_BT_RESET };
	Serial1.begin(bt_Baud);

	pinMode(pin_BT_ENABLE, OUTPUT); digitalWrite(pin_BT_ENABLE, 0);
	pinMode(pin_BT_STATE, INPUT);

	for (int i = 0; i < 7; i++) {
		pinMode(BT_AUDIO[i], OUTPUT);
	}
	pinMode(pin_BT_ENABLE, OUTPUT); digitalWrite(pin_BT_ENABLE, 0);

	return;
}
void iniciar_declarar::dispositivos() {
	analogWriteResolution(12);

}
void iniciar_declarar::outputs() {
	Serial.println("Se estan inicializando SALIDAS");
	for (int i = 0; i < 4; i++) {
		pinMode(pin_RGBW[i], OUTPUT);
	}

	pinMode(pin_IR_LED, OUTPUT);
	pinMode(pin_PIEZO, OUTPUT); digitalWrite(pin_PIEZO, 0);
	pinMode(pin_HDMI_SELEC, OUTPUT);

}
void iniciar_declarar::inputs() {
	const char pin_HDMI[3] = { pin_HDMI_1, pin_HDMI_2, pin_HDMI_3 }; //
	Serial.println("Se estan inicializando ENTRADAS");
	//ADC
	pinMode(pin_AMPERIMETRO, INPUT);
	pinMode(pin_NIVEL_BATERIA, INPUT);
	pinMode(pin_TEMP_LM35, INPUT);
	pinMode(pin_MQ2_ANALOGICO, INPUT);
	pinMode(pin_I2C_INTERRUPCION, INPUT);
	pinMode(pin_MQ_2, INPUT_PULLUP);
	pinMode(pin_micro, INPUT);
	pinMode(pin_PIR, INPUT);
	pinMode(pin_DETECTOR_PUERTA, INPUT);
	pinMode(pin_ONOFF_ESTUFA, INPUT);
	pinMode(pin_IR_RECIVE, INPUT);
	for (int i = 0; i < 3; i++) {
		pinMode(pin_HDMI[i], INPUT);
	}	
}

void interrupciones::init(void) {
	Serial.println("Se estan inicializando INTERRUPCIONES");
	attachInterrupt(digitalPinToInterrupt(pin_I2C_INTERRUPCION),
		i2c_interrupcion, RISING);
	attachInterrupt(digitalPinToInterrupt(pin_MQ_2),
		MQ_2_interrupcion, RISING);
	attachInterrupt(digitalPinToInterrupt(pin_PIR),
		pir_interrupcion, RISING);
}
void interrupciones::temporalizador(unsigned long retraso,
	unsigned long *tiempo_control, void( *funcion)()) {
	if (*tiempo_control < millis()) {
		*tiempo_control = retraso + millis();
		funcion(); 
	}
}
bool interrupciones::temporalizadorBool(unsigned long retraso,
	unsigned long* tiempo_control){
	if (*tiempo_control < millis()) {
		*tiempo_control = retraso + millis();
		return true;
	}
	return false;
}

