#include <ESP8266WiFi.h>

const uint8_t NUMBER_PLOTS = 6;

const char* ssid = "your_ssid";
const char* password = "your_password";
const char* host = "ip_address_your_server";
const uint16_t port = 40029;//your connection port

WiFiClient client;

//Relay is connected to these pins
uint8_t plots[NUMBER_PLOTS] = { D0, D1, D2, D3, D4, D5 };


void setup() {
  for (int i = 0; i < NUMBER_PLOTS; i++) {
    pinMode(plots[i], OUTPUT);
    digitalWrite(plots[i], HIGH);//HIGH because using relay LOW level, if you use relay HIGH level change HIGH for LOW
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(3000);
  }
}

void loop() {
  if (client.connected()) {
    String command = "";
    while (client.available()) {
      char ch = static_cast<char>(client.read());
      command += ch;
    }
    if (command == "stop")
      stop();
    else {
      if (command.length() != 0 && command.length() == 3) {
        if (command[0] == 'R') {
          uint8_t plotNumber = command[1] - '0';
          uint8_t signal = command[2] - '0';
          digitalWrite(plots[plotNumber], !signal);//!signal for relay LOW level, if you use relay HIGH level delete '!' before signal 
        }
      }
    }
  } else {
    client.connect(host, port);
  }
}

void stop() {
  for (int i = 0; i < NUMBER_PLOTS; i++) {
    digitalWrite(plots[i], HIGH);
  }
}

