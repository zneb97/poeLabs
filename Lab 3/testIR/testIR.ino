String tuning = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

//Code from user Alvaro Luis Bustamante from
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
  if (Serial.available() > 0) {
                // read the incoming byte:
                //income = Serial.readString();
                tuning = Serial.readString();
                var = getValue(tuning, '&', 0);
                value = getValue(tuning, '&', 1);

  }
}
