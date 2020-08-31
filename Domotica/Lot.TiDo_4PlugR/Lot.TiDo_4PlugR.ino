#include "LoT.TiDo_OTA.h"
#include "Lot.TiDo_CONNECTWiFi.h"
#include "Lot.TiDo_Blynk_4lightR.h"
#include <ESP8266WiFi.h>
#include "Defaults_2LightR.h"

char blynk_Key[34] = "";
void test() {
    
}
void setup() {
    pinMode(light_0, OUTPUT); digitalWrite(light_0, 0);
    pinMode(light_1, OUTPUT); digitalWrite(light_1, 0);
    pinMode(light_switch_0, INPUT);
    pinMode(light_switch_1, INPUT);
 
   // Serial.begin(74880); Serial.println();
   // Serial.print(sistem);
   // Serial.print(" Debug: "); Serial.println(device);
  //  wifi_data(device_, sistem, password_d);
   // wifi_data("2LightR", "Lot.TiDo", "12345678");
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
    
    //else 
      //  Serial.println("Conecto blynk"); 
}

void loop() {
   init_interrupciones();
   api_Run();
   OTA_RUN();    
}
