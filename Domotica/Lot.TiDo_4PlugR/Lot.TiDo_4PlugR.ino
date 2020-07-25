#include "Lot.TiDo_CONNECTWiFi.h"
#define light_0         0
#define light_1         1
#define light_switch_0  2
#define light_switch_1  3
#define device          "Test"


void setup() {
    pinMode(light_0, OUTPUT); digitalWrite(light_0, 0);
    pinMode(light_1, OUTPUT); digitalWrite(light_1, 0);
    pinMode(light_switch_0, INPUT);
    pinMode(light_switch_1, INPUT);
    Serial.println("HOla");
    wifi_data(device);
    LotSetup();

}

void loop() {

}