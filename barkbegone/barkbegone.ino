#include "EspMQTTClient.h"
#include "credentials.h"

#define BUZZ_PIN 2
#define BUZZ_DURATION_DEFAULT 3
#define MQTT_TOPIC_SUB "home/remote/barkbegone"

EspMQTTClient client(
  WIFI_NETWORK,
  WIFI_PASS,
  MQTT_SERVER,
  MQTT_USER,
  MQTT_PASS,
  MQTT_PORT
);

void setup() {
  pinMode(BUZZ_PIN, OUTPUT);
}

void loop() {
  //
}
