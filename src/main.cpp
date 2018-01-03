#include "Arduino.h"
#include <RCSwitch.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>

#define BROKER "" //TODO: your mqtt broker ip address or url
#define BROKER_PORT 1883 //TODO: your mqtt port
#define TOPIC "" //TODO: your mqtt topic
#define MQTT_USER "" //TODO: your username
#define MQTT_PASS "" //TODO: your password
#define CLIENT_ID "" //TODO: your client id

#define WIFI_SSID "" //TODO: your wifi SSID
#define WIFI_PASS "" //TODO: your wifi password
#define TRANSMITER_PIN 13 // the GPIO that your transmiter data pin is connected. GPIO13 here

ESP8266WiFiMulti wifi;
WiFiClient wifiClient;
PubSubClient clientMQTT(wifiClient);

RCSwitch mySwitch = RCSwitch();

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
  char inData[length];
  StaticJsonBuffer<200> jsonBuffer;

  Serial.print("payload: ");
  for(int i =0; i<length; i++){
    Serial.print((char)payload[i]);
    inData[(i)] = (char)payload[i];
  }
  Serial.println();

  JsonObject& root = jsonBuffer.parseObject(inData);

  int protocol = root["protocol"];
  int pulseLength = root["pulse_length"];
  const char* binary = root["binary"];

  mySwitch.setProtocol(protocol);
  mySwitch.setPulseLength(pulseLength);
  mySwitch.send(binary);
}

void connectToBroker() {
  while (!clientMQTT.connected()) {
    Serial.println("Trying to connect to MQTT broker");
    if (clientMQTT.connect(CLIENT_ID)) {
      Serial.print("Connected to the Broker!");
      clientMQTT.subscribe(TOPIC);
    } else {
      Serial.print("failed! try again in 5s");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);

  mySwitch.enableTransmit(TRANSMITER_PIN);

  wifi.addAP(WIFI_SSID, WIFI_PASS);

  Serial.println();
  Serial.println("Waiting for WiFi...");

  while (wifi.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("Connected to WiFi!");
  Serial.println("Your IP Address is:");
  Serial.println(WiFi.localIP());

  clientMQTT.setServer(BROKER, BROKER_PORT);
  clientMQTT.setCallback(callback);
}

void loop() {
  if (!clientMQTT.connected()) {
    connectToBroker();
  }
  clientMQTT.loop();
}
