// 
// 
// 

#include <FS.h>          // this needs to be first, or it all crashes and burns...
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>

#ifdef ESP32
#include <SPIFFS.h>
#endif

#include "Lot.TiDo_CONNECTWiFi.h"
char api_token[34] = "";
char auth[34] = "";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";
char name_AP[32] = "Lot.TiDo_Default"; //Lot.TiDo 4PlugR
char default_AP[] = "Lot.TiDo ";
int Hola = 0;
bool shouldSaveConfig = false;

//callback notifying us of the need to save config
void saveConfigCallback() {
    Serial.println("Should save config");
    shouldSaveConfig = true;
}

void setupSpiffs() {
    //read configuration from FS json
    Serial.println("mounting FS...");

    if (SPIFFS.begin()) {
        Serial.println("mounted file system");
        if (SPIFFS.exists("/config.json")) {
            //file exists, reading and loading
            Serial.println("reading config file");
            File configFile = SPIFFS.open("/config.json", "r");
            if (configFile) {
                Serial.println("opened config file");
                size_t size = configFile.size();
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                json.printTo(Serial);
                if (json.success()) {
                    Serial.println("\nparsed json");
                    strcpy(api_token, json["api_token"]);
                    strcpy(auth, api_token);
                }
                else {
                    Serial.println("failed to load json config");
                }
            }
        }
    }
    else {
        Serial.println("failed to mount FS");
    }
    //end read
}

void LotSetup() {

    Serial.begin(74880);
    Serial.println();

    setupSpiffs();
// WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;
//set config save notify callback
    wm.setSaveConfigCallback(saveConfigCallback);
// setup custom parameters
    WiFiManagerParameter custom_api_token("api", "Blynk Token", "", 32);
//add all your parameters here
    wm.addParameter(&custom_api_token);

    if (!wm.autoConnect(name_AP, "12345678")) {
        Serial.println("failed to connect and hit timeout");
        delay(3000);
        // if we still have not connected restart and try all over again
        ESP.restart();
        delay(5000);
    }

    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    strcpy(api_token, custom_api_token.getValue());
    //

    //save the custom parameters to FS
    if (shouldSaveConfig) {
        Serial.println("saving config");
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.createObject();
        json["api_token"] = api_token;
        strcpy(auth, custom_api_token.getValue());
        File configFile = SPIFFS.open("/config.json", "w");
        if (!configFile) {
            Serial.println("failed to open config file for writing");
        }
        json.prettyPrintTo(Serial);
        json.printTo(configFile);
        configFile.close();
        //end save
        shouldSaveConfig = false;
    }

    Serial.println("local ip");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.gatewayIP());
    Serial.println(WiFi.subnetMask());
    Serial.print("blynk token: ");
    Serial.println(auth);
  // Blynk.begin(auth, NULL, NULL);
   // Blynk.syncAll();
  
}

void lotLoop() {
    // put your main code here, to run repeatedly:
   // Blynk.run();
}

void wifi_data(char nameAP[]) {
    strcpy(name_AP, strcat(default_AP, nameAP));
}
void get_key(char key_blynk[]) {
    
    strcpy(key_blynk, auth);

}