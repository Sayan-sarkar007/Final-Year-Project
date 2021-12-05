#include <Servo.h>


#define numOfValsRec 5
#define digitsPerValRec 1


Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;

int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1; //$00000
int count = 0;
bool countStart = false;
String recivedString;



void setup() {
  Serial.begin(9600);
 
  servoThumb.attach(7);
  servoIndex.attach(6);
  servoMiddle.attach(5);
  servoRing.attach(4);
  servoPinky.attach(3);
}

void reciveData(){
  
  while(Serial.available())
  {
    char c = Serial.read();
    
    if( c == '$'){
      countStart = true;
    }
    if(countStart){
      if(count < stringLength){
        recivedString = String(recivedString+c);
        count++;
      }
      if( count >= stringLength){
        for( int i = 0; i<numOfValsRec; i++){
          int num = (i* digitsPerValRec)+1;
          valsRec[i] = recivedString.substring(num, num + digitsPerValRec ).toInt();
        }
        recivedString = "";
        count = 0;
        countStart = false;
      }
    }

  }
}


void loop() {
  
  reciveData();
  if(valsRec[0] == 1 ){servoThumb.write(180);}else{servoThumb.write(0);}
  if(valsRec[1] == 1 ){servoIndex.write(180);}else{servoIndex.write(0);}
  if(valsRec[2] == 1 ){servoMiddle.write(180);}else{servoMiddle.write(0);}
  if(valsRec[3] == 1 ){servoRing.write(180);}else{servoRing.write(0);}
  if(valsRec[4] == 1 ){servoPinky.write(180);}else{servoPinky.write(0);}

}
