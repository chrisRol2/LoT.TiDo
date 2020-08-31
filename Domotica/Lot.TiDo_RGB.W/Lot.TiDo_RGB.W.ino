/*
 Name:		Lot.ino
 Created:	24/07/2020 0:03:19
 Author:	chris
*/

#include "Lot.TiDo_Blynk_RGB.h"
#include "LoT.TiDo_OTA.h"
#include "Lot.TiDo_CONNECTWiFi.h"

#include "Default_RGB.h"

char blynk_Key[34] = "";


void setup() {
    pinMode(RED_PIN, OUTPUT); digitalWrite(RED_PIN, 1);
    pinMode(GREEN_PIN, OUTPUT); digitalWrite(GREEN_PIN, 1);
    pinMode(BLUE_PIN, OUTPUT); digitalWrite(BLUE_PIN, 2);

    setupSpiffs();
    WiFiManager_setup();
    get_key(blynk_Key);
    OTA_SETUP(device_, password_d);

    if (!api_connect(blynk_Key)) {
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
    api_Run();
    OTA_RUN();

}
