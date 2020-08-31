// 
// 
// 
#include "Lot.TiDo_CONNECTWiFi.h"
#include <FS.h>          // this needs to be first, or it all crashes and burns...
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson
#include <ESP8266WiFi.h>


//define your default values here, if there are different values in config.json, they are overwritten.
char    api_token[34] = "";
char    password_default[32] = "12345678";
char    name_default[32] = "AutoConnect_Def";
//void setupSpiffs();
void saveConfigCallback();
WiFiManager wm;

void wifi_data(char nameAP[], char nameSIS[] , char passwordDEF[]) {
    strcat(nameSIS, " ");
    strcpy(name_default, strcat(nameSIS, nameAP));
    strcpy(password_default, passwordDEF);
}
void get_key(char key_blynk[]) {
    strcpy(key_blynk, api_token);
}

void clear_Data() {
    wm.resetSettings();
    WiFiManager_setup();// ESP.restart();
}

//callback notifying us of the need to save config
bool shouldSaveConfig = false;
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

void WiFiManager_setup() {
    // WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
   

    //set config save notify callback
    wm.setSaveConfigCallback(saveConfigCallback);

    WiFiManagerParameter custom_api_token("api", "Blynk's Token", api_token, 32);

    //add all your parameters here

    wm.addParameter(&custom_api_token);

    if (!wm.autoConnect(name_default, password_default)) {
   // if (!wm.autoConnect("Hola", "12345678")) {
        Serial.println("failed to connect and hit timeout");
        delay(3000);
        // if we still have not connected restart and try all over again
        ESP.restart();
        delay(5000);
    }
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");

    //read updated parameters

    strcpy(api_token, custom_api_token.getValue());

    //save the custom parameters to FS
    if (shouldSaveConfig) {
        Serial.println("saving config");
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.createObject();

        json["api_token"] = api_token;
        

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
    Serial.print("api_token: "); Serial.println(api_token);
    Serial.println("local ip");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.gatewayIP());
    Serial.println(WiFi.subnetMask());
    Serial.println("Conectado!");

}