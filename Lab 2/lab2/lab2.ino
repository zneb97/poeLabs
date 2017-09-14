
//Tilt pan numbers
int resolution = 10; //How many divisions per axis
int servoDeg = 200; //Degrees servo can rotate through

//Distance in cm to be considered the object
int distance = 20; 

//Sensor port
int IR = 0;

//Servo ports
Servo pan;
Servo tilt;

void setup() {
  // Make sure the baud rate is the same as in sendReceive.py
  Serial.begin(9600);

  //Setup servos
  pan.attach(8);
  tilt.attach(9);

}

void loop() {
  //Th
  for(int i = 0; i<resolution/servoDeg


  //Stops arduino from running full speed
  delay(10);

}
