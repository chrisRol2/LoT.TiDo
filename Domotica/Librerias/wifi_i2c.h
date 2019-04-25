// wifi_i2c.h

#ifndef _WIFI_I2C_h
#define _WIFI_I2C_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif
#include "reloj.h"
class wifiN{
	private:
		int i2c_dir;
		//reloj_calendario reloj;
	public:
		wifiN(int _i2c_dir): i2c_dir(_i2c_dir){}
		void config(void);
		void reset(void);
		int	 getHora(void);
		int	 getMinutos(void);
		int	 getSegundos(void);
		int	 getDia(void);
		int	 getDiaS(void);
		int	 getMes(void);
		int	 getAnio(void);
		int	 getCelsius(void);
		int	 getHumedad(void);
		int	 getHIC();
		bool getBtEn(void);
		bool getDoor(void);
		bool getWifi(void);

	};