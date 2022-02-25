
#include "MPU9250.h"

MPU9250 mpu;

unsigned long previousMillis = 0;
const long interval = 100; 
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
}

void loop() {
  
  unsigned long currentMillis = millis();
  mpu.update();
  
  if(currentMillis - previousMillis >= interval) {
      print_roll_pitch_yaw();
      previousMillis = currentMillis;
  }
    
}

void print_roll_pitch_yaw() {
    Serial.print(mpu.getYaw(), 2);
    Serial.print(",");
    Serial.print(mpu.getPitch(), 2);
    Serial.print(",");
    Serial.println(mpu.getRoll(), 2);
}
