//Blank serial inits
String tuning = "";
String var = "";
String value = "";

//PID Coefficents
float kp = 1;
float ki = 1;
float kd = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

//Code by user Alvaro Luis Bustamante from
//https://stackoverflow.com/questions/9072320/split-string-into-string-array

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void loop() {
  //Get tuning values from serial and update coefficents
  if (Serial.available() > 0) {
                // read the incoming byte:
                //income = Serial.readString();
                tuning = Serial.readString();
                var = getValue(tuning, '&', 0);
                value = getValue(tuning, '&', 1);
                if(var=="p"){
                  kp=value;
                }
                else if(var=="i"){
                  ki = value;
                }
                else if(var=="d"){
                  kd = value;
                }

  }

  //Run motors

  
}
