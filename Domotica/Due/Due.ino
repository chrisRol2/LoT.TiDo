/*
 * DUE.ino
 *
 * Created: 4/2/2019 11:18:27 PM
 * Author:	Christoher Roldan Sanchez
 * Email:	Christopher_rol@hotmail.es
 *
 */
#include "estados_esp8266.h"
#include "configuracion.h"
#include "estados.h"

estado does(0);
iniciar_declarar IO(19200, 9600);											//objeto que declara IO, Comunicaciones 


void setup() {
	IO.serial();
	IO.outputs();
	IO.inputs();
	IO.dispositivos();
	IO.memoriaSD();
	does.config();
}

void loop() {
	does.permanente();														// estado que se repite permanentemente
	does.select_estado();													// aqui se selecciona el estado actual
}