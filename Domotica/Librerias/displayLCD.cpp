/*
 * displayLCD.cpp
 *
 * Created: 4/2/2019 11:18:27 PM
 * Author:	Christoher Roldan Sanchez
 * Email:	Christopher_rol@hotmail.es
 */

#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include "displayLCD.h"
#include "pinesIO.h"
#include "interrupciones.h"
#include <Wire.h>
#include "version.h"

byte grados_c[8] = {
	B01000,
	B10100,
	B01000,
	B00011,
	B00100,
	B00100,
	B00011,
};
byte closed[8] = {
	B00000,
	B01110,
	B10001,
	B10001,
	B11111,
	B11011,
	B11111,
};
byte opened[8] = {
	B00110,
	B01001,
	B01001,
	B00001,
	B11111,
	B11011,
	B11111,
	B00000,
};
byte IconWIFI[8] = {
	B00000,
	B11111,
	B00000,
	B01110,
	B00000,
	B00100,
	B00000,
	B00000,
};
byte speed_icon[8] = {
	B00000,
	B01010,
	B00100,
	B01010,
	B00000,
	B11111,
	B01110,
	B00100,
};
byte bt_icon[8] = {
	B00100,
	B00110,
	B10101,
	B01110,
	B01110,
	B10101,
	B00110,
	B00100,
};
byte estufa_icon[8] = {
	B11110,
	B10010,
	B10000,
	B10111,
	B10000,
	B10010,
	B11110,
	B00000,
};
byte reloj_icon[8] = {
	B01110,
	B10001,
	B10101,
	B10111,
	B10001,
	B10001,
	B01110,
	B00000,
};

display::display(uint8_t _adr, String _version, int _fila, int _columnas) : LiquidCrystal_PCF8574(_adr) {

	version = _version;
	filas = _fila;
	columnas = _columnas;
}

void display::customCharALL() {
	createChar(0, opened);
	createChar(1, closed);
	createChar(2, grados_c);
	createChar(3, IconWIFI);
	createChar(4, speed_icon);
	createChar(5, bt_icon);
	createChar(6, estufa_icon);
	createChar(7, reloj_icon);

}

bool display::init() {
	Wire.begin();
	Wire.beginTransmission(0x27);
	if (Wire.endTransmission() == 0) {
		Serial.println("LCD encontrado.");
	}
	else {
		Serial.print(" LCD no encontrado.");
		errores(2);
		return 1;
	}
	pinMode(pin_BRILLO_LCD, OUTPUT);
	digitalWrite(pin_BRILLO_LCD, brilloV);
	begin(columnas, filas);
	return 0;
}

void display::encender(uint8_t como = 0) {
	Serial.println("Encendiendo display");
	volatile uint8_t delay_pe = 5;
	home(); clear();
	for (volatile int i = 0; i < 4096; i++) {
		brillo(i);
		if (como) {
			if (i == 255) {
				setCursor(5, 0);
				print("## HOLA ##");
			}
			if (i == 521) {
				setCursor(5, 2);
			}
			if (i == 3000) {
				setCursor(8, 3);
				print(VERSION);
				setCursor(6, 2);
				print(NAME);
				Serial.println(version);
			}
		}
		if (i == 128) {
			home();
			clear();
		}
	}
}

void display::apagar(uint8_t como = 0) {
	Serial.println("Apagando display");
	for (int i = 4095; 0 < i; i--) {
		brillo(i);
		if (como) {
			if (i == 3584) {
				home(); clear();
				setCursor(3, 0);
				print("## ADIOS ##");
			}
			if (i == 3200) {
				setCursor(3, 1);
				print(version);
				Serial.println(version);
			}
			if (i == 128) home(); clear();
		}
	}

}

void display::imprimir(int x, int y, String dato) {

	setCursor(x, y);
	print(dato);

}

void display::imprimir(int x, int y, int dato) {// entero

	setCursor(x, y);
	print(dato);
}

void display::gotoxy(int x, int y) {
	if (x == -1) {
		for (int i = 0; i < y; i++) {
			print(" ");
		}
		return;
	}
	setCursor(x, y);
}

void display::brillo(uint32_t _brilloV = 255) {
	setBacklight(255);
	brilloV = _brilloV;
	analogWrite(pin_BRILLO_LCD, brilloV);
	if (brilloV == 0) {
		setBacklight(0);
	}
}

void display::printFecha(int x, int y, int dia, int dia_semana, int mes, int anio) {
	const String dias[] = { "Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab" };
	const String meses[] = { "Ene","Feb","Mar","Abr","May","Jun","Jul","Ago","Sep","Oct","Nov","Dic" };
	gotoxy(x, y);
	print(dias[1]); print(" ");
	print(dia);
	print(" ");
	print(meses[mes]);

}

void display::printHora(int x, int y, int hora, int minutos, int segundos) {
	gotoxy(x, y);
	if (hora < 10 && hora > -1)print("0");
	print(hora); print(":");
	if (minutos < 10 && minutos > -1) print("0");
	print(minutos);
}

void display::printSimbolo(int x, int y, int simbolo) {
	gotoxy(x, y);
	write(simbolo);
}

void display::reset() {
	home(); clear(); setBacklight(255);
	noBlink(); /*display(); */noCursor();
}

void display::printClima(int x, int y, int valor, int valorF, int tipoClima) {
	gotoxy(x, y);
	switch (tipoClima) {
	case temperaturaC:// temp
		print(valor);
		
		write(2);
		break;
	case temperaturaH: //humedad
		print(valor);
		print("%");
		break;
	case temperaturaHIC: // indice de calor
		print("HiC: ");
		print(valor);
		write(2);
		break;
	default:
		break;
	}
}
void display::printBT(int x, int y, bool BT_ESTADO) {
	gotoxy(x, y);
	if (BT_ESTADO)write(5);
	else print(" ");
}
void display::printWiFi(int x, int y, bool WIFI_ESTADO) {
	gotoxy(x, y);
	if (WIFI_ESTADO)write(3);
	else print(" ");
}