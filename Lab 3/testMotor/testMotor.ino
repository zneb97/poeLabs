#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//Setup motor shield
  Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
  Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

void setup() {
  Serial.begin(9600);

  AFMS.begin();
  myMotor->setSpeed(0);

}

void loop() {
  // put your main code here, to run repeatedly:

}
