#ifndef _serialOTA_

#define _serialOTA_

#include <arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

#define SERIAL_OTA_N_CLIENTS_MAX    1
#define SERIAL_OTA_PORT             23
#define BUFFER_SIZE                 32

class SerialOTA;
extern SerialOTA serialOTA;

class SerialOTA
{
public:
  static void begin();
  static void loop();
  static void println(const char* str);
private:
  static WiFiServer server;
  static WiFiClient clients[];
  static uint8_t  buffer[];
  static uint8_t bufferIdx;
  static void readData();
  static void checkConnection();
};


#endif
