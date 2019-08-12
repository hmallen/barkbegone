#include <FS.h>

#include <ArduinoJson.h>
#include <WiFiManager.h>

#define BUZZ_PIN 2

char mqtt_server[40];
char mqtt_port[6] = "8080";
char blynk_token[34] = "Stuff&Things";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(BUZZ_PIN, OUTPUT);
  digitalWrite(BUZZ_PIN, LOW);

  Serial.begin(115200);

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
        //DynamicJsonDocument jsonBuffer(1024);
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        //deserializeJson(jsonBuffer, buf);
        json.printTo(Serial);
        //serializeJson(jsonBuffer, Serial);
        if (json.success()) {
          //if (!jsonBuffer.isNull()) {
          Serial.println("\nparsed json");

          strcpy(mqtt_server, json["mqtt_server"]);
          //strcpy(mqtt_server, jsonBuffer["mqtt_server"]);
          strcpy(mqtt_port, json["mqtt_port"]);
          //strcpy(mqtt_port, jsonBuffer["mqtt_port"]);
          strcpy(blynk_token, json["blynk_token"]);
          //strcpy(blynk_token, jsonBuffer["blynk_token"]);

        }
        else {
          Serial.println("failed to load json config");
        }
        configFile.close();
      }
    }
  }
  else {
    Serial.println("failed to mount FS");
  }
  //end read

  WiFiManager wm;

  /*wm.resetSettings();
    Serial.print("DEBUG...");
    while (true) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    }
    Serial.println("done.");*/

  if (!wm.autoConnect("CrumbopulousMichael", "BlipsAndChips")) {
    Serial.println(F("Failed to connect. Restarting in 5 seconds."));
    delay(5000);
    ESP.restart();
  }
  else {
    Serial.println(F("Connected."));
    digitalWrite(BUZZ_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZ_PIN, LOW);
  }
}

void loop() {
  //
}
