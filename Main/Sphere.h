#ifndef Sphere_H
#define Sphere_H

#include <Arduino.h>
#include <FastLED.h>

#define LED_TYPE WS2812B

class Sphere
{

private:
  int NUM_PER_STRIP[19] = {300, 300, 300, 300, 300,
                           300, 300, 300, 300, 300,
                           300, 300, 300, 300, 300,
                           300, 300, 300, 300};

//    int NUM_PER_STRIP[19] = {15, 15, 15, 15, 15,
//                             15, 15, 15, 15, 15,
//                             15, 15, 15, 15, 15,
//                             15, 15, 15, 15}; 

  int Total_LEDS;
  int NUM_STRIPS = 19;
  int BRIGHTNESS = 50;
  CRGBPalette16 currentPalette;
  TBlendType currentBlending;
  // extern CRGBPalette16 myRedWhiteBluePalette;
  // extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
  CRGB leds[19][300];

public:
  //    Sphere(int PINS[19], int NUM_LEDS[19], int NUM_STRIPS, int BRIGHTNESS){
  //      this->PINS = PINS;
  //      this->NUM_LEDS = NUM_LEDS;
  //      this->NUM_STRIPS = NUM_STRIPS;
  //      this->BRIGHTNESS = BRIGHTNESS;
  //    }

  Sphere()
  {
    sum();
  }

  void sum()
  {
    int suma = 0;
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      suma += NUM_PER_STRIP[i];
    }
    Total_LEDS = suma;
  }

  // Power on the LED
  void setPins()
  {

    // currentPalette = RainbowColors_p;
    // currentBlending = LINEARBLEND;

    FastLED.addLeds<WS2812B, 2, GRB>(leds[0], NUM_PER_STRIP[0]);
    FastLED.addLeds<WS2812B, 4, GRB>(leds[1], NUM_PER_STRIP[1]);
    FastLED.addLeds<WS2812B, 5, GRB>(leds[2], NUM_PER_STRIP[2]);
    FastLED.addLeds<WS2812B, 18, GRB>(leds[3], NUM_PER_STRIP[3]);
    FastLED.addLeds<WS2812B, 19, GRB>(leds[4], NUM_PER_STRIP[4]);
    FastLED.addLeds<WS2812B, 21, GRB>(leds[5], NUM_PER_STRIP[5]);
    FastLED.addLeds<WS2812B, 22, GRB>(leds[6], NUM_PER_STRIP[6]);
    FastLED.addLeds<WS2812B, 23, GRB>(leds[7], NUM_PER_STRIP[7]).setCorrection(TypicalLEDStrip);
    ;

    FastLED.addLeds<WS2812B, 12, GRB>(leds[8], NUM_PER_STRIP[8]);
    FastLED.addLeds<WS2812B, 13, GRB>(leds[9], NUM_PER_STRIP[9]);
    FastLED.addLeds<WS2812B, 14, GRB>(leds[10], NUM_PER_STRIP[10]);
    FastLED.addLeds<WS2812B, 27, GRB>(leds[11], NUM_PER_STRIP[11]);

    FastLED.addLeds<WS2812B, 12, GRB>(leds[8], NUM_PER_STRIP[8]);
    FastLED.addLeds<WS2812B, 13, GRB>(leds[9], NUM_PER_STRIP[9]);
    FastLED.addLeds<WS2812B, 14, GRB>(leds[10], NUM_PER_STRIP[10]);
    FastLED.addLeds<WS2812B, 27, GRB>(leds[11], NUM_PER_STRIP[11]);

    FastLED.addLeds<WS2812B, 26, GRB>(leds[12], NUM_PER_STRIP[12]);
    FastLED.addLeds<WS2812B, 25, GRB>(leds[13], NUM_PER_STRIP[13]);
    FastLED.addLeds<WS2812B, 32, GRB>(leds[14], NUM_PER_STRIP[14]);
    FastLED.addLeds<WS2812B, 33, GRB>(leds[15], NUM_PER_STRIP[15]);

    FastLED.addLeds<WS2812B, 16, GRB>(leds[16], NUM_PER_STRIP[16]);
    FastLED.addLeds<WS2812B, 17, GRB>(leds[17], NUM_PER_STRIP[17]);
    FastLED.addLeds<WS2812B, 1, GRB>(leds[18], NUM_PER_STRIP[18]);

    FastLED.setBrightness(BRIGHTNESS);
  }

  void simpleColor(int hue)
  {
    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      for (int j = 0; j < NUM_PER_STRIP[i]; j++)
      {
        leds[i][j] = CHSV(hue, 255, 255);
      }
    }
    FastLED.show();
  }

  void intensity(int hue, int intensity)
  {
    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      for (int j = 0; j < NUM_PER_STRIP[i]; j++)
      {
        leds[i][j] = CHSV(hue, 255, 255 * (intensity / 100));
      }
    }
    FastLED.show();
  }

  void rainbow(int increment)
  {
    FastLED.clear();
    int offset = increment % 255;
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      int hue = map(i, 0, NUM_STRIPS, 0, 255);
      for (int j = 0; j < NUM_PER_STRIP[i]; j++)
      {
        leds[i][j] = CHSV((hue + offset) % 255, 255, 255);
      }
    }
    FastLED.show();
  }

  void fadeOne(int strip, int center, int color)
  {
    int len = NUM_PER_STRIP[strip];
    float newCenter = (center % len);
    for (int j = 0; j < len; j++)
    {
      float distance;

      if ((newCenter - j) > len * 0.5)
      {
        distance = abs(newCenter - (j + len));
      }
      else if ((newCenter - j) < -(len * 0.5))
      {
        distance = abs(newCenter - j + len);
      }
      else
      {
        distance = abs(newCenter - j);
      }

      float grad = 1 - (distance / len) * 4;
      int atenuacion = mapF(grad, 0, 1, 0, 255);
      // console.log(col);
      leds[strip][j] = CHSV(color, 255, atenuacion);
    }
  }

  void fadeAll(float center, int color)
  {
    FastLED.clear();
    // int offset = increment % 255;
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      fadeOne(i, center, color);
    }
    FastLED.show();
  }

  void porcentaje(float percentage, int color)
  {

    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      for (int j = 0; j < NUM_PER_STRIP[i]; j++)
      {
        if (j < percentage)
        {
          leds[i][j] = CHSV(color, 255, 255);
        }
      }
    }
    FastLED.show();
  }

  void danceFalf(int counter, int ratio, int color)
  {
    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      halfLeds(i, counter + i*ratio, 200);
    }
    FastLED.show();
  }

  void halfLeds(int strip, int counter, int color)
  {
    for (int j = 0; j < NUM_PER_STRIP[strip]; j++)
    {
      if (j < NUM_PER_STRIP[strip] / 2)
      {
        int xoff = (j + counter) % NUM_PER_STRIP[strip];
        leds[strip][xoff] = CHSV(color, 255, 255);
      }
    }
  }

  void movible(float percentage, int color)
  {

    FastLED.clear();
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      for (int j = 0; j < 20; j++)
      {
        if (floor((percentage / 100) * 20) < j)
        {
          leds[i][j] = CHSV(color, 255, 255);
        }
      }
    }
    FastLED.show();
  }

  void partitionOne(int strip, int parts, int intensity, int color){
    int l = NUM_PER_STRIP[strip];
    int ratio = round(l/parts);
    for (int j = 0; j < NUM_PER_STRIP[strip]; j++) {
      if(j%ratio == 0){
        leds[strip][j] = CHSV(color, 255, 255* (intensity/100));
      }
    }
  }

void partitionAll(int count, int parts, int color){
  
  for (int i = 0; i < NUM_STRIPS; i++){
    for (int j = 0; j < NUM_PER_STRIP[i]; j++){
      int yoff = (i + count) % NUM_STRIPS;
      if (i < NUM_STRIPS / 2) {
        partitionOne(yoff, 5, 1, color);
      } else {
        partitionOne(yoff, 5, 0.4, color);
      }
    }
  }
}

  float modulo(float x, float y, float z)
  {
    return sqrt(x * x + y * y + z * z);
  }

  void simpleChangePaletteGyro(float yaw)
  {
    simpleColor(yaw);
  }
  void ChangePaletteGyro(float vector[])
  {
    float yaw = vector[0];
    float pitch = vector[1];
    float roll = vector[2];

    if (pitch > 50 && roll < 45 && yaw > 45)
    {
      simpleColor(0);
    }
    if (pitch < 50 && roll < 45 && yaw > 45)
    {
      simpleColor(30);
    }
    if (pitch > 50 && roll < 45 && yaw > 45)
    {
      simpleColor(60);
    }
    if (pitch > 50 && roll < 45 && yaw < 45)
    {
      simpleColor(90);
    }
    if (pitch < 50 && roll > 45 && yaw > 45)
    {
      simpleColor(120);
    }
    if (pitch < 50 && roll < 45 && yaw < 45)
    {
      simpleColor(180);
    }
    if (pitch > 50 && roll > 45 && yaw < 45)
    {
      simpleColor(210);
    }
    if (pitch < 50 && roll > 45 && yaw < 45)
    {
      simpleColor(240);
    }
  }

  float mapF(float value, float start1, float stop1, float start2, float stop2)
  {
    float outgoing = start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
    return outgoing;
  }
};

#endif
