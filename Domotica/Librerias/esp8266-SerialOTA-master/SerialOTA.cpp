#include "SerialOTA.h"


SerialOTA serialOTA;

WiFiServer SerialOTA::server(SERIAL_OTA_PORT);
WiFiClient SerialOTA::clients[SERIAL_OTA_N_CLIENTS_MAX];
uint8_t  SerialOTA::buffer[BUFFER_SIZE];
uint8_t SerialOTA::bufferIdx  =0;

void SerialOTA::begin()
{
  server.begin();
  server.setNoDelay(true);

};


void SerialOTA::readData()
{
  //check clients for data and copy to buffer
  for(uint8_t i = 0; i < SERIAL_OTA_N_CLIENTS_MAX; i++)
  {
    if (clients[i] && clients[i].connected())
    {
      if(clients[i].available())
      {
        //get data from the telnet client and push it to the UART
        while(clients[i].available()) 
        {
          bufferIdx += clients[i].read(buffer+bufferIdx,BUFFER_SIZE-bufferIdx);

          if (bufferIdx>BUFFER_SIZE)
          {
              println("buffer overflow\n\r");
              bufferIdx = 0;
          }
          if ((bufferIdx>0) && (buffer[bufferIdx-1] == '\n'))
          {
              buffer[bufferIdx-1] = '\0';
              println("string received: ");
              println((const char*)buffer);
              println("\n\r");
              bufferIdx = 0;
          }
        }
      }
    }
  }
  
  
};


void SerialOTA::checkConnection()
{
  
  if (server.hasClient())
  {
    for(uint8_t i = 0; i < SERIAL_OTA_N_CLIENTS_MAX; i++)
    {
      //find free/disconnected spot
      if (!clients[i] || !clients[i].connected())
      {
        if(clients[i]) clients[i].stop();
        clients[i] = server.available();
        continue;
      }
    }
    //no free/disconnected spot so reject
    WiFiClient serverClient = server.available();
    serverClient.stop();
  }
  
}

void SerialOTA::loop()
{

  checkConnection();
  readData();


};


void SerialOTA::println(const char* str)
{

  for(uint8_t i = 0; i < SERIAL_OTA_N_CLIENTS_MAX; i++)
  {
      if (clients[i] && clients[i].connected())
      {
        clients[i].write(str);
      }
  }   
      
  
}

