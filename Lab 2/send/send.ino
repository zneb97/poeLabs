#include <Servo.h>

//Tilt pan numbers
int resolutionX = 30; //How many divisions per axis
int servoDegX = 30; //Degrees servo can rotate through

int resolutionY = 70; //How many divisions per axis
int servoDegY = 70; //Degrees servo can rotate through

//Start positions
int posX = 0;
int posY = 30;

//Sensor port
int IR = 0;

//Servo objects
Servo pan;
Servo tilt;

//button pin
int button = 10;

void setup() {
  // Make sure the baud rate is the same as in sendReceive.py
  Serial.begin(9600);

  //Setup servos
  pan.attach(8);
  tilt.attach(9);
  pan.write(posX);
  tilt.write(30);

  //Setup button
  pinMode(button, INPUT);
}

//Sends angle and distance data to python
void sendData(int x, int y){
    //Take three distances and average them
    int take1 = analogRead(IR);
    delay(5);
    int take2 = analogRead(IR);
    delay(5);
    int take3 = analogRead(IR);
    float avg = (take1+take2+take3)/3.0;

    //Send to python, let it do distance calculations
    Serial.println(String(x) + "&" + String(y) + "&" + String(avg));

}

void loop() { 
  if(digitalRead(button)){
    //Start command to python script
    Serial.println("Start");

    for(posY = 30; posY <= servoDegY; posY += servoDegY/resolutionY){
      tilt.write(posY);
     
      for (posX = 0; posX <= servoDegX; posX += servoDegX/resolutionX) {
        pan.write(posX);            
        sendData(posY,posX);
        delay(100);
      }
    }

    //Stop commadn to python script
    Serial.println("Stop");

    //Reset position for next run
    tilt.write(30);
    pan.write(0);
  }
  
}
