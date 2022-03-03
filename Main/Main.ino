#include "MainServer.h"
#include "Sphere.h"
#include "Counter.h"

//MainServer test(8);
Sphere light;
Counter helper;
MainServer accessPoint("accessPoint");
int counter = 0;
AsyncWebServer server(80);
float artistas[3] = {0.0, 0.0, 0.0};

//Direcciones de cada bailarin
const char dir0[] = "/b0";
const char dir1[] = "/b1";
const char dir2[] = "/b2";
const char *direcciones[3] = {dir0, dir1, dir2};


void setup() {
  Serial.begin(115200);
  accessPoint.setAccess();
  light.setPins();

  for (int i = 0; i < 2; i++) {
    helper.increment();
    //Colocar un listener por cada dirección de cada baliarin (cliente)
    server.on(direcciones[i], HTTP_GET, [](AsyncWebServerRequest * request) {
      int artista = helper.getCount();
      //Añadir otro parametro por cada valor a recoger (yaw, pitch ...)
      if (request->hasParam("yaw")) {
        //recoge cada valor de un parámetro
        String yawS = request->getParam("yaw")->value();
        String pitchS = request->getParam("pitch")->value();
        String rollS = request->getParam("roll")->value();

        float yaw = yawS.toFloat();
        float pitch = pitchS.toFloat();
        float roll = rollS.toFloat();

        artistas[0] = yaw;
        artistas[1] = pitch;
        artistas[2] = roll;
        
        
        //print_roll_pitch_yaw(yaw, pitch, roll);
        //guardar los datos en la clase MainServer
        //accessPoint.setArtista(yaw, artista, 0);
        //accessPoint.setArtista(pitch, artista, 1);
        //accessPoint.setArtista(roll, artista, 2);
        Serial.println();
      } else {
        //Valor de error
        Serial.println("Error");
      }
      request->send_P(200, "text/plain", "Bien");
    });
  }

  // Start server
  server.begin();
}

void loop() {
  //Animaciones
  //accessPoint.printArtista(0);
  //light.simpleColor(160);
  //Serial.println(counter);
 
  light.rainbow(counter);
  
  counter = artistas[0];
  printArtista();
  //accessPoint.setArtista(counter, 0, 0);
  //Serial.println(accessPoint.getArtista(0, 0));
  //light.simpleChangePaletteGyro(accessPoint.getArtista(0)[0]);
  //Serial.println(counter);
  delay(5);
}

void print_roll_pitch_yaw(float yaw, float pitch, float roll) {
  Serial.print(yaw, 2);
  Serial.print(",");
  Serial.print(pitch, 2);
  Serial.print(",");
  Serial.println(roll, 2);
}

void printArtista(){
  Serial.print("Artista: ");
  Serial.print(0);
  for(int j = 0; j < 3; j++){
      Serial.print("    ");
      Serial.print(artistas[j]);
    }
    Serial.println();
}
