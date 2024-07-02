#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>

const char* networkName = ""; // SSID here
const char* password = ""; // Password here

const char receiveServerAddress[] = ""; // Add the address of the website api you want to receive the data from
const char sendServerAddress[] = ""; // Add the address of the website data-save.php file you want to send the data to

StaticJsonDocument<700> doc;

const int interval = 1800000; // 30 mins

WiFiClientSecure client;
HTTPClient http;

int i = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(networkName, password);
  delay(5000);
  WiFi.begin(networkName, password);
}

void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    dataTransmit();

    Serial.print("Sending\n");
    delay(interval);
  } else {
    Serial.print("Failed\n");
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(++i);
      Serial.print(' ');
    } 
    return;
  }
}

void dataTransmit() {
  client.setInsecure();
  if (http.begin(client, receiveServerAddress)) {
    http.addHeader("Api", "Api-code"); // Set the website's api code you're trying to receive the data from if neccessery
    int receiveHttpResponseCode = http.GET();

    if (receiveHttpResponseCode > 0) {
      String payload = http.getString();
      DeserializationError errorCheck = deserializeJson(doc, payload);

      if(!errorCheck) {
        float value1 = doc[]; // Navigate to the data you want to get using the JSON you receive
        // Add more data here

        serializeJsonPretty(doc, Serial);
        Serial.println();

        Serial.println(value1);

        http.end();
        
        if (http.begin(client, sendServerAddress)) {
          http.addHeader("Content-Type", "application/x-www-form-urlencoded");

          String postData = "value1=" + String(value1); // Add and send more data here
          
          int sendHttpResponseCode = http.POST(postData);
          if (receiveHttpResponseCode > 0) {
            http.end();
          }
        }
      }
    }
  }
}
