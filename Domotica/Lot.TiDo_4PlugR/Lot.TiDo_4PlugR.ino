#include "Lot.TiDo_CONNECTWiFi.h"
#include "Lot.TiDo_Blynk_4lightR.h"
#include <ESP8266WiFi.h>

#define light_0         0
#define light_1         1
#define light_switch_0  2
#define light_switch_1  3
#define device          "2LightR"
#define sistem          "Lot.TiDo"
#define password        "12345678"

char blynk_Key[34] = "";

void setup() {
    pinMode(light_0, OUTPUT); digitalWrite(light_0, 0);
    pinMode(light_1, OUTPUT); digitalWrite(light_1, 0);
    pinMode(light_switch_0, INPUT);
    pinMode(light_switch_1, INPUT);
    Serial.begin(74880); Serial.println();
    Serial.print(sistem);
    Serial.print(" Debug: "); Serial.println(device);
    wifi_data(device, sistem, password);
    setupSpiffs();
    WiFiManager_setup();
    get_key(blynk_Key);
    if (!api_connect(blynk_Key)) {
        Serial.println("No conecto blynk");
        if (!isTokenValid()) {
            clear_Data();
        }
        else /*
                funcion en blynk que  compruebe conexion a wifi
                si hay wifi controlar si hay conexion a internet, hacer un ping
                si no hay internet, abrir una web para conectar el wifi de vuelta
                o cambiar valores, interruptores en la web

             */
    }
    else { 
        Serial.println("Conecto blynk"); 
    }
}

void loop() {
    Serial.println("Entra en el Loop");
    while (true)
    {
        api_Run();
    }
}
