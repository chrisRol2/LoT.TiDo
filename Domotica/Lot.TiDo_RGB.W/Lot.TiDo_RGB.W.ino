/*
*	File:   Lot.TiDo_RGB.W.ino
*	Author:	Christopher Roldan Sanchez
*	Mail:	Christopher_Rol@hotmail.es
*   Web:    https://www.lot-tido.com
*	Date:
*	Description:	
*
*/

#include "Lot.TiDo_Blynk_RGB.h"
#include "LoT.TiDo_OTA.h"
#include "Lot.TiDo_CONNECTWiFi.h"
#include "Default_RGB.h"

char blynk_Key[34] = "";
char blynk_Key2[34] = "";


void setup() {
    pinMode(RED_PIN, OUTPUT); digitalWrite(RED_PIN, 1);
    pinMode(GREEN_PIN, OUTPUT); digitalWrite(GREEN_PIN, 1);
    pinMode(BLUE_PIN, OUTPUT); digitalWrite(BLUE_PIN, 1);

    wifi_data(device_, sistem, password_d);

    setupSpiffs();
    WiFiManager_setup();
    get_key(blynk_Key);
    get_key2(blynk_Key2);
    OTA_SETUP(device_, password_d);

    if (!api_connect(blynk_Key,blynk_Key2)) {
        //  Serial.println("No conecto blynk");
        if (!isTokenValid()) {
            // clear_Data();
            // WiFiManager_setup();
            //get_key(blynk_Key);
        }
        else { /*
               funcion en blynk que  compruebe conexion a wifi
               si hay wifi controlar si hay conexion a internet, hacer un ping
               si no hay internet, abrir una web para conectar el wifi de vuelta
               o cambiar valores, interruptores en la web
               */
        }
    }
   
}

// the loop function runs over and over again until power down or reset
void loop() {

    if( connected_wifi() ) {
        OTA_RUN();
    }
    if( connected() ) {
        api_Run();
    }
    else {
        static long retardment = 0;
        if( millis() > retardment ) {
            api_connect(blynk_Key, blynk_Key2);
            retardment = millis() + RECONNECTION_TIME;
        }
    }
    offline_funcions();
}
