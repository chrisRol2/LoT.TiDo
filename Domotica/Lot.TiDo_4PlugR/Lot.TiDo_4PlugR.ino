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
    pinMode(light_switch_0, INPUT_PULLUP);
    pinMode(light_switch_1, INPUT_PULLUP);
 
    Serial.begin(74880); Serial.println();
    Serial.print(sistem);
    Serial.print(" Debug: "); Serial.println(device);
    wifi_data(device, sistem, password_d);
    setupSpiffs();
    WiFiManager_setup();
    get_key(blynk_Key);
    if (!api_connect(blynk_Key)) {
        Serial.println("No conecto blynk");
        if (!isTokenValid()) {
            clear_Data();
            WiFiManager_setup();
            get_key(blynk_Key);
        }
        else { /*
                funcion en blynk que  compruebe conexion a wifi
                si hay wifi controlar si hay conexion a internet, hacer un ping
                si no hay internet, abrir una web para conectar el wifi de vuelta
                o cambiar valores, interruptores en la web
             */
        }
    }
    else 
        Serial.println("Conecto blynk"); 

    detachInterrupt(digitalPinToInterrupt(light_switch_0));
    //attachInterrupt(digitalPinToInterrupt(light_switch_0),test,LOW);

}

void loop() {
    Serial.println("Entra en el Loop");
   // init_interrupciones();
    while (true)
    {
        api_Run();
    }
}
