//LED pin numbers
int LED_RED_1 = 13;
int LED_GREEN_1 = 12;
int LED_YELLOW = 11;
int LED_GREEN_2 = 10;
int LED_RED_2 = 9;

//Button pin numbers
int BUTTON = 8;

//Axis analog pin numbers
int YAXIS = 0;

//Bike lamp modes
// 0 = all off
// 1 = all on
// 2 = all flashing
// 3 = two on - three on
// 4 = line flash
int mode = 0;

//Debounce
unsigned long lastTime = 0;
unsigned long delayTime = 500;

//newDelayTime
int joyDelayTime = 500;

//Flag variable to restart loops
int flag = 0;

void setup() {
  Serial.begin(9600);

  //LED pin modes
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_GREEN_1, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN_2, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);

  //Button pin mode
  pinMode(BUTTON, INPUT);

}

//Set pins to corresponding output
void setPins(int p1, int p2, int p3, int p4, int p5) {
  digitalWrite(LED_RED_1, p1);
  digitalWrite(LED_GREEN_1, p2);
  digitalWrite(LED_YELLOW, p3);
  digitalWrite(LED_GREEN_2, p4);
  digitalWrite(LED_RED_2, p5);

}

//Custome delay to allow for interrupt with joy input
bool newDelay(){
  int wait = makeDelay();
  unsigned long startTime = millis();
  while((millis()-startTime) < wait){
    if(checkButton()){
      return true;
    }
    //Delay to stop Arduino from running full spee
    delay(5);
  }
  return false;
}

//Overloaded function for user defined wait
bool newDelay(int wait){
  unsigned long startTime = millis();
  while((millis()-startTime) < wait){
    if(checkButton()){
      return true;
    }
    //Delay to stop Arduino from running full spee
    delay(5);
  }
  return false;
}

bool checkButton(){
    //Button press check
    if (digitalRead(BUTTON) == 1) {
      //Debounce time elapsed check
      if ((millis() - lastTime) > delayTime) {
        Serial.println("triggered");
        mode++;
        //Loop over modes
        if (mode > 4) {
          mode = 0;
        }
        lastTime = millis();
        return true;
    }
    else{
      Serial.println("refused");
    }
  }
  return false;
}

//Set up delay based on joystick
int makeDelay(){
  long axis = analogRead(YAXIS);
  //joyDelayTime = (1/1000.0)*(axis*axis*1.0)+(-2.5*axis)+2000;
  joyDelayTime = map(axis, 0, 1023, 1000,250);
  return joyDelayTime;
}

void loop() {
  checkButton();
  
  //All off
  if (mode == 0) {
    setPins(0, 0, 0, 0, 0);
  }
  
  //All on
  else if (mode == 1) {
    setPins(1, 1, 1, 1, 1);
  }
  
  //Flashing
  else if (mode == 2) {
    flag = 0;
    while(flag == 0){
      setPins(1, 1, 1, 1, 1);
      if(newDelay()){
        break;
      }
      setPins(0, 0, 0, 0, 0);
      if(newDelay()){
        break;
      }
      flag == 1;
    }
  }

  //Two on, three on
  else if (mode == 3) {
    flag = 0;
    while(flag == 0){
      setPins(0, 1, 0, 1, 0);
      if(newDelay()){
        break;
      }
      setPins(1, 0, 1, 0, 1);
      if(newDelay()){
        break;
      }
      flag == 1;
    }
  }
  
  //Line flash
  else if (mode == 4) {
    flag = 0;
    while(flag == 0){
      setPins(1, 0, 0, 0, 0);
      if(newDelay()){
        break;
      }
      setPins(0, 1, 0, 0, 0);
      if(newDelay()){
        break;
      }
      setPins(0, 0, 1, 0, 0);
      if(newDelay()){
        break;
      }
      setPins(0, 0, 0, 1, 0);
      if(newDelay()){
        break;
      }
      setPins(0, 0, 0, 0, 1);
      if(newDelay()){
        break;
      }
      setPins(0, 0, 0, 1, 0);
      if(newDelay()){
        break;
      }
      setPins(0, 0, 1, 0, 0);
      if(newDelay()){
        break;
      }
      setPins(0, 1, 0, 0, 0);
      if(newDelay()){
        break;
      }
      setPins(1, 0, 0, 0, 0);
      if(newDelay()){
        break;
      }
      flag == 1;
    }
  }

  //Delay to stop Arduino from running full speed
  delay(5);
  
}


