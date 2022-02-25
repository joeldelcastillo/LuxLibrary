#include "MainServer.h"
#include "Sphere.h"
#include "Counter.h"

//MainServer test(8);
Sphere light;
Counter helper;
MainServer accessPoint("accessPoint");
AsyncWebServer server(80);

//Direcciones de cada bailarin
const char dir0[] = "/b0";
const char dir1[] = "/b1";
const char dir2[] = "/b2";
const char *direcciones[3] = {dir0, dir1, dir2};


void setup() {
  Serial.begin(115200);
  accessPoint.setAccess();
  light.setPins();

  for(int i = 0; i < 2; i++){
    helper.increment();
    //Colocar un listener por cada dirección de cada baliarin (cliente)
    server.on(direcciones[i], HTTP_GET, [](AsyncWebServerRequest *request){
      
      int artista = helper.getCount();
      //Añadir otro parametro por cada valor a recoger (yaw, pitch ...)
      if (request->hasParam("yaw")){
        float value;
        //recoge cada valor de un parámetro
          String message = request->getParam("yaw")->value();
          value = message.toFloat();
          //guardar los datos en la clase MainServer
          accessPoint.setArtista(value, artista, 0);
          Serial.printf("yaw: %d,/n", value);
         
      } 
      if (request->hasParam("pitch")){
        float value;
        //recoge cada valor de un parámetro
          String message = request->getParam("pitch")->value();
          value = message.toFloat();
          //guardar los datos en la clase MainServer
          accessPoint.setArtista(value, artista, 1);
          Serial.printf("pitch: %d,/n",value);
          
      }
      if (request->hasParam("roll")){
        float value;
        //recoge cada valor de un parámetro
          String message = request->getParam("roll")->value();
          value = message.toFloat();
          //guardar los datos en la clase MainServer
          accessPoint.setArtista(value, artista, 2);
          Serial.printf("pitch: %d,/n",value);
      }
      else {
       
      }
      request->send_P(200, "text/plain", "Bien");
    });
  }
  
  // Start server
  server.begin();
}

void loop() {
  //Animaciones

  
  //light.simpleColor(160);
  //Serial.println("hola");
  //light.rainbow(counter);
  light.ChangePaletteGyro(accessPoint.getArtista(0));
  //delay(1);
}
