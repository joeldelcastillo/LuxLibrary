#ifndef Counter_H
#define Counter_H

#include <Arduino.h>

// Clase helper para incrementar dentro de un lambda
class Counter
{

private:
  int count = 0;

public:
  void increment()
  {
    count++;
  }

  int getCount()
  {
    return count;
  }

    int getCount(int num)
  {
    return num;
  }
};

#endif
