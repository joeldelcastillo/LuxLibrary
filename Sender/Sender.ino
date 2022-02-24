#include <WiFi.h>
#include <HTTPClient.h>
#include "MPU9250.h"

MPU9250 mpu;

const char* ssid = "ESP32";
const char* password = "123456789";

//Your Domain name with URL path or IP address with path
String serverNameCounter = "http://192.168.4.1/b0";

unsigned long previousMillis = 0;
const long interval = 500; 
HTTPClient http;
float value = 0;

void setup() {

  
  Serial.begin(115200); 

  //MPU connection
  Wire.begin();

  if (!mpu.setup(0x68)) {
    while (1) {
      Serial.println("MPU connection failed");
      delay(5000);
    }
  }

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");

}

void loop() {
  
  unsigned long currentMillis = millis();
  mpu.update();
  
  if(currentMillis - previousMillis >= interval) {
     if(WiFi.status()== WL_CONNECTED){
      //POST request
      String serverPath = httpPOSTRequest(serverNameCounter, "count", mpu.getYaw());
      
      http.begin(serverPath.c_str());
      // Send HTTP GET request
      int httpResponseCode = http.GET();

      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    previousMillis = currentMillis;
  }
    
}


//Crea un sring para enviar por parámetros cada valor
String httpPOSTRequest(String serverName, String param, float value) {
    String serverPath = serverName + "?" + param + "=" + String(value, 3);
    Serial.println(param + "=" + String(value, 3));
    return serverPath;
}
