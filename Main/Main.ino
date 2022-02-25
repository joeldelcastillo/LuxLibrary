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
      float value;
      int artista = helper.getCount();
      //Añadir otro parametro por cada valor a recoger (yaw, pitch ...)
      if (request->hasParam("count")){
        //recoge cada valor de un parámetro
          String message = request->getParam("count")->value();
          value = message.toFloat();
          //guardar los datos en la clase MainServer
          accessPoint.setArtista(value, artista, 0);
          Serial.println(value);
      } else {
        //Valor de error
        value = 999;
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
  //delay(1);
}
