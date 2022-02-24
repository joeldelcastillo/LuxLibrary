#ifndef Sphere_H
#define Sphere_H

#include <Arduino.h>
#include <FastLED.h>

#define LED_TYPE WS2812B


class Sphere {
  
  private:
    int NUM_PER_STRIP[19] = {300, 300, 300, 300, 300, 
                             300, 300, 300, 300, 300, 
                             300, 300, 300, 300, 300, 
                             300, 300, 300, 300};
    int Total_LEDS;
    int NUM_STRIPS = 19;
    int BRIGHTNESS = 50;

//    LinkedList<LinkedList<CRGB>> leds;
//    vector<vector<CRGB>> leds;
    CRGB leds[19][300];
//    
  public:


//    Sphere(int PINS[19], int NUM_LEDS[19], int NUM_STRIPS, int BRIGHTNESS){
//      this->PINS = PINS;
//      this->NUM_LEDS = NUM_LEDS;
//      this->NUM_STRIPS = NUM_STRIPS;
//      this->BRIGHTNESS = BRIGHTNESS;
//    }

    Sphere(){
      sum();
    }

    void sum(){
      int suma = 0;
      for (int i = 0; i < NUM_STRIPS; i ++){
        suma += NUM_PER_STRIP[i];
      }
      Total_LEDS = suma;
    }
    

    // Power on the LED
    void setPins(){
      
      FastLED.addLeds<WS2812B, 2, GRB>(leds[0], NUM_PER_STRIP[0]);
      FastLED.addLeds<WS2812B, 4, GRB>(leds[1], NUM_PER_STRIP[1]); 
      FastLED.addLeds<WS2812B, 5, GRB>(leds[2], NUM_PER_STRIP[2]); 
      FastLED.addLeds<WS2812B, 18, GRB>(leds[3], NUM_PER_STRIP[3]); 
      FastLED.addLeds<WS2812B, 19, GRB>(leds[4], NUM_PER_STRIP[4]); 
      FastLED.addLeds<WS2812B, 21, GRB>(leds[5], NUM_PER_STRIP[5]);
      FastLED.addLeds<WS2812B, 22, GRB>(leds[6], NUM_PER_STRIP[6]);
      FastLED.addLeds<WS2812B, 23, GRB>(leds[7], NUM_PER_STRIP[7]);

      
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

    void simpleColor(int hue){
      
      
      for (int i = 0; i < NUM_STRIPS; i++)
      {
        for (int j = 0; j < NUM_PER_STRIP[i]; j++)
        {
          leds[i][j] = CHSV(hue, 255, 255);
          
          }
       }
       
    }

      void rainbow(int increment){
        FastLED.clear();
        int offset = increment % 255;
        for (int i = 0; i < NUM_STRIPS; i++)
        {
          int hue = map(i, 0, NUM_STRIPS, 0, 255);
          for (int j = 0; j < NUM_PER_STRIP[i]; j++)
          {
            leds[i][j] = CHSV((hue + offset)%255, 255, 255);
            }
         }
         FastLED.show();
      }


};

#endif
