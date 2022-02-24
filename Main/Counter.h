#ifndef Counter_H
#define Counter_H

#include <Arduino.h>

//Clase helper para incrementar dentro de un lambda
class Counter {
  
  private:
    int count = 0;
    
  public:
    // Setup pin LED and call init()

    void increment(){
      count++;
    }

    int getCount(){
      return count;
    }
  

};

#endif
