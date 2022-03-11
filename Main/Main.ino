#include "MainServer.h"
#include "Sphere.h"
#include "Counter.h"

// MainServer test(8);
Sphere light;
Counter helper;
MainServer accessPoint("accessPoint");
int counter = 0;
int accVar = 0;
int anim = 0;
float maxBailarin = 0;

AsyncWebServer server(80);
float artista0[4] = {0.0, 0.0, 100, 0.0};
float artista1[4] = {0.0, 0.0, 180, 0.0};
float artista2[4] = {0.0, 0.0, 0.0, 0.0};
float artista3[4] = {0.0, 0.0, 0.0, 0.0};

// Direcciones de cada bailarin
const char dir0[] = "/b0";
const char dir1[] = "/b1";
const char dir2[] = "/b2";
const char *direcciones[3] = {dir0, dir1, dir2};

void setup()
{
  Serial.begin(115200);
  light.setPins();
  accessPoint.setAccess();
  for (int i = 0; i < 2; i++)
  {
    // Colocar un listener por cada dirección de cada baliarin (cliente)
    server.on(direcciones[i], HTTP_GET, [](AsyncWebServerRequest * request)
    {
      // Añadir otro parametro por cada valor a recoger (yaw, pitch ...)
      if (request->hasParam("yaw"))
      {
        // recoge cada valor de un parámetro
        String yawS = request->getParam("yaw")->value();
        String pitchS = request->getParam("pitch")->value();
        String rollS = request->getParam("roll")->value();
        String accS = request->getParam("acc")->value();
        String idS = request->getParam("id")->value();

        float yaw = yawS.toFloat();
        float pitch = pitchS.toFloat();
        float roll = rollS.toFloat();
        float acc = accS.toFloat();
        int id = idS.toInt();

        switch (id) {
          case 0:
            artista0[0] = yaw;
            artista0[1] = pitch;
            artista0[2] = roll;
            artista0[3] = acc;
            break; // optional
          case 1:
            artista1[0] = yaw;
            artista1[1] = pitch;
            artista1[2] = roll;
            artista1[3] = acc;
            break; // optional
          case 2:
            artista2[0] = yaw;
            artista2[1] = pitch;
            artista2[2] = roll;
            artista2[3] = acc;
            break; // optional
          case 3:
            break; // optional
        }
        request->send_P(200, "text/plain", "Bien");

        // printVars(id, yaw, pitch, roll, acc);
        // guardar los datos en la clase MainServer
        // accessPoint.setArtista(yaw, artista, 0);
        // accessPoint.setArtista(pitch, artista, 1);
        // accessPoint.setArtista(roll, artista, 2);
        // Serial.println();
      }
      else if (request->hasParam("anim"))
      {
        // Valor de error
        String animS = request->getParam("anim")->value();
        anim = animS.toInt();
        request->send_P(200, "text/plain", "Bien Animado");
      }
    });
  }
  // Start server
  server.begin();
}

void loop()
{

  counter++;
  switch (anim)
  {
    case 0:
      light.halfLeds(counter, 50);
      break; // optional
    case 1:
      light.movible(artista1[3] * 100, 100);
      break; // optional
    case 2:
      light.simpleColor(artista1[3] * 250);
      break; // optional
    case 3:
      light.intensity(50, round(artista1[3] * 100));
      break; // optional
  }
}

// printArtista1();
//  Animaciones
//  accessPoint.printArtista(0);
//  light.simpleColor(160);
//  Serial.println(counter);

// light.rainbow(counter);
//   counter++;

// accVar += artista1[2]/150;
// light.intensity(50, round (artista0[3] * 100));
// light.halfLeds(round(accVar), 50);
// light.halfLeds(counter, 50);
// counter++;

// counter = light.modulo(artistas[0], artistas[1], artistas[2]);
// float percentage = mapF(counter, 0, 2, 0, 100);
// light.intensity(100, percentage);

// Serial.println();
// light.movible(percentage, 100);

// Serial.println(percentage);
// light.simpleColor(counter);

// light.ChangePaletteGyro(artistas);

// printArtista();
// accessPoint.setArtista(counter, 0, 0);
// Serial.println(accessPoint.getArtista(0, 0));
// light.simpleChangePaletteGyro(accessPoint.getArtista(0)[0]);
// Serial.println(counter);

void printVars(int artista, float yaw, float pitch, float roll, float acc)
{
  Serial.print("Artista: ");
  Serial.print(artista);
  Serial.print(": ");
  Serial.print(yaw, 2);
  Serial.print(",");
  Serial.print(pitch, 2);
  Serial.print(",");
  Serial.print(roll, 2);
  Serial.print(",");
  Serial.println(acc, 2);
}

void printArtista0()
{

  Serial.print("Artista: ");
  Serial.print(0);
  for (int j = 1; j < 4; j++)
  {
    Serial.print("    ");
    Serial.print(artista0[j]);
  }
  Serial.println();
}

void printArtista1()
{

  Serial.print("Artista: ");
  Serial.print(1);
  for (int j = 1; j < 4; j++)
  {
    Serial.print("    ");
    Serial.print(artista1[j]);
  }
  Serial.println();
}

void printArtista2()
{

  Serial.print("Artista: ");
  Serial.print(2);
  for (int j = 1; j < 4; j++)
  {
    Serial.print("    ");
    Serial.print(artista2[j]);
  }
  Serial.println();
}
