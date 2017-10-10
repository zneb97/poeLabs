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

//Base speed
float ratio = .6; //Due to physical differences in the motor
int rBaseSpeed = 75;
int lBaseSpeed = int(round(rBaseSpeed*ratio));

//PID coefficents
//Editable via serial
int kp = 1;
int ki = 1;
int kd = 1;

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

  Serial.println(leftValue-rightValue);
}
