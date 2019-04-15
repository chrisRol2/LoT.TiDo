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
		void imprimir(uint8_t x, uint8_t y, String dato);
		void imprimir(uint8_t x, uint8_t y, int dato);
		void gotoxy(int x, int y);
		void printFecha( uint8_t x, uint8_t y,int dia, int dia_semana, int mes, int anio);
		void printHora(uint8_t x, uint8_t y, int hora, int minutos, int segundos);
		void printSimbolo(uint8_t x, uint8_t y, int simbolo);
		void reset();
		void printClima(uint8_t x, uint8_t y, uint8_t valor, uint8_t valorF, int tipoClima);
		void printBT(uint8_t x, uint8_t y, bool BT_ESTADO);
		void printWiFi(uint8_t x, uint8_t y, bool WIFI_ESTADO);
	
};

