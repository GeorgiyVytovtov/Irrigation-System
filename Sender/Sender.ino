#include <MCP3008.h>
#include <ESP8266WiFi.h>

const uint8_t NUMBER_SOIL_MOISTURE_SENSORS = 6;

const char* ssid = "your_ssid";
const char* password = "your_password";
const char* host = "ip_address_your_server";
const uint16_t port = 40029;//your connection port

unsigned long lastTime;

WiFiClient client;

MCP3008 adc(D5, D7, D6, D8);

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(3000);
  }
  delay(500);
}


void loop() {
  if (client.connected()) {
    if (millis() - lastTime < 0) {
      lastTime = 0;
    }
    if (millis() - lastTime > 60000) {
      lastTime = millis();
      String dataWithAllSensors = getDataWithSensors();
      client.write(dataWithAllSensors.length() + 1);
      client.print("D" + dataWithAllSensors);
    }
  } else {
    client.connect(host, port);
  }
}

String getDataWithSensors() {
  String dataWithAllSensors = "";
  uint8_t i = 0;
  while (i < NUMBER_SOIL_MOISTURE_SENSORS) {
    int moistureValue = adc.readADC(i);
    int moistureValuePercent = map(moistureValue, 0, 1023, 100, 0);
    dataWithAllSensors += String(moistureValuePercent);
    dataWithAllSensors += ';';
    i++;
    delay(10);
  }
  dataWithAllSensors.remove(dataWithAllSensors.length() - 1);
  return dataWithAllSensors;
}



