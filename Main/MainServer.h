#ifndef MainServer_H
#define MainServer_H

#include <Arduino.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

class MainServer {
  
  private:
    const char* ssid = "ESP32";
    const char* password = "123456789";
    const String severName1 = "http://192.168.4.1/counter";
    String serverName = "";
    float artistas[5][3] = {
                          {0.0, 0.0, 0.0},
                          {0.0, 0.0, 0.0},
                          {0.0, 0.0, 0.0},
                          {0.0, 0.0, 0.0},
                          {0.0, 0.0, 0.0},
                          };
    
    int pin;
    
  public:
    // Setup pin LED and call init()
    MainServer(String serverName){
      this->serverName = serverName;
    }

    void setAccess(){
            // Setting the ESP as an access point
      Serial.print("Setting AP (Access Point)…");
      // Remove the password parameter, if you want the AP (Access Point) to be open
      WiFi.softAP(ssid, password);
    
      IPAddress IP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(IP);  
    }

    void setArtista(float value, int artista, int angle){
      artistas[artista][angle] = value;
    }
  

};

#endif
