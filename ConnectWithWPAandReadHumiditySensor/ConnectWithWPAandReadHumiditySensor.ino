#include <SPI.h>
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include <stdio.h>
#include <string.h>

char* ssid = "Grog Esteso";     //  your network SSID (name)
char* pass = "A043AE7C9C";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

int idx = 2;
char* ipPort = "192.168.1.93:8080";

void setup() {  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // wait 1 second for connection:
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");
  printCurrentNet();
  printWifiData();
}

void loop() {
  int data = (1000 - analogRead(17))/7.5;
  Serial.print("Sending data to server: ");
  Serial.print(data);
  Serial.println();
  HTTPClient http;
  char msg[95];
  snprintf(msg, 95, "http://%s/json.htm?type=command&param=udevice&idx=%d&nvalue=%d&svalue=%d", ipPort, idx, data, data);
  Serial.println(msg);
  http.begin(msg);

  int httpCode = http.GET();
  Serial.print("http code: ");
  Serial.print(httpCode);
  Serial.println();

  delay(1000);
  http.end();
  // check the network connection once every 10 seconds:
  delay(10000);
  printCurrentNet();
}

void printWifiData() {
}

void printCurrentNet() {
}

