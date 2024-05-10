#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
char msg;
char call;
int flag = 0;
#define motor 13
#define led 4

void setup(){
  pinMode(motor,OUTPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("GSM SIM900A BEGIN");
  Serial.println("Sending message");
      mySerial.println("AT+CMGF=1");
      delay(1000);
      mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r");
      delay(1000);
      mySerial.println("Ready");
      delay(100);
      mySerial.println((char)26);
      delay(1000);
}

void loop(){
    
    if(isIncomingCall()==true){
      switch(flag){
        case 1:
          digitalWrite(motor,LOW);
          mySerial.println("AT+CMGF=1");
          delay(1000);
          mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r");
          delay(1000);
          mySerial.println("the motor is turnt off");
          delay(100);
          mySerial.println((char)26);
          delay(1000);
          flag=0;
          break;
         case 0:
          digitalWrite(motor,HIGH);
          mySerial.println("AT+CMGF=1");
          delay(1000);
          mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r");
          delay(1000);
          mySerial.println("the motor is turnt on");
          delay(100);
          mySerial.println((char)26);
          delay(1000);
          flag=1;
          break;
         default:
          break;
        }
      
      }
  
  }

bool isIncomingCall() {
  mySerial.println("ATA"); // Answer incoming call
  delay(1000);
  
  while (mySerial.available()) {
    String response = mySerial.readStringUntil('\n');
    if (response.indexOf("RING") != -1) {
      delay(1000);
      Serial.println("call recieved");
      delay(1000);
      mySerial.println("ATH");
      return true; // Incoming call detected
    }
  }
  return false; // No incoming call detected
}
