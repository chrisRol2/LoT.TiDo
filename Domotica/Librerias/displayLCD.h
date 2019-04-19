// displayLCD.h

#ifndef _DISPLAYLCD_h
#define _DISPLAYLCD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif
#include <LiquidCrystal_PCF8574.h>
#define temperaturaC	1
#define temperaturaH	2
#define temperaturaHIC	3

class display : public LiquidCrystal_PCF8574{
	private:
		String version;
		int filas;
		int columnas;
		uint32_t brilloV;
	public:	
		display(uint8_t, String, int, int);
		void customCharALL();
		bool init();
		void brillo(uint32_t _brilloV);
		void encender(uint8_t como);
		void apagar(uint8_t como);
		void imprimir(int x, int y, String dato);
		void imprimir(int x, int y, int dato);
		void gotoxy(int x, int y);
		void printFecha(int x, int y,int dia, int dia_semana, int mes, int anio);
		void printHora(int x, int y, int hora, int minutos, int segundos);
		void printSimbolo(int x, int y, int simbolo);
		void reset();
		void printClima(int x, int y, int valor, int valorF, int tipoClima);
		void printBT(int x, int y, bool BT_ESTADO);
		void printWiFi(int x, int y, bool WIFI_ESTADO);
	
};

