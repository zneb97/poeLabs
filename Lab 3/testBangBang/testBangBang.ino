#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


//Setup motor shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);

//Setup IR sensors
int leftIR = 1;
int rightIR = 0;
int leftValue = 600;
int rightValue = 600;
int threshold = 700;

int dir = 0;

//Base speed
float ratio = .6; //Due to physical differences in the motor
int rBaseSpeed = 75;
int lBaseSpeed = int(round(rBaseSpeed*ratio));


void setup() {
  Serial.begin(9600);

  //Motors init settings
  AFMS.begin();
  leftMotor->run(FORWARD); //Change these as needed
  rightMotor->run(BACKWARD);
  leftMotor->setSpeed(0);
  rightMotor->setSpeed(0);
  

}

void loop() {
  //Get sensor data
  leftValue = analogRead(leftIR);
  rightValue = analogRead(rightIR);
  String printString = String(leftValue) + '\t' + String(rightValue);
  Serial.println(printString);

  //Turning left
  if (dir == 0){
    leftMotor->setSpeed(lBaseSpeed*.25);
    rightMotor->setSpeed(rBaseSpeed);
    if (rightValue > threshold){
      dir = 1;
    }
  }

  //Turning right
  else{
    leftMotor->setSpeed(lBaseSpeed);
    rightMotor->setSpeed(rBaseSpeed*.25);
    if (leftValue > threshold){
      dir = 0;
    }
  }
  


}
