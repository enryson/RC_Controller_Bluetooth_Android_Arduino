
#include <Servo.h>
//#include <SoftwareSerial.h>
#include <Arduino.h>

#define buser 8
//SoftwareSerial mySerial(2, 3);
Servo myservo,esc;

//string
String inString = "";

unsigned long startTime;
unsigned long otherTime;

int prev = 150;

float vPow = 5;
float r1 = 100000.00;
float r2 = 10000.00;



int voltcheck = 0;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(8,OUTPUT);
  myservo.attach(6);//Carrinho
  esc.attach(5);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  myservo.write(120);
  getv();
}

void loop() {
  if (Serial.available() > 0) {
    int inChar = Serial.read();
    
    if (isDigit(inChar)) {
      inString += (char)inChar; 
    }
    
    if (inChar == 'n'){
      int n = inString.toInt();
      if (n <= 180){
        //Serial.println(n);
        myservo.write(n);        
      }
      inString = "";
    }
    if (inChar == 'r') {
      int x = inString.toInt();
      if (x <= 165){
        //Serial.println(x);
        esc.write(x);      
      }
      inString = "";
    }    
    if (inChar == 'm') {      
      if (voltcheck > 10){
      getv();
      voltcheck = 0;
      }
      else {
        voltcheck = voltcheck + 1;
      }
      digitalWrite(13, HIGH);
      startTime = millis();
    }
  }
}
static void getv() {
  float v = ((analogRead(1)+40) * vPow) / 1023.0;
    float v2 = v / (r2 / (r1 + r2));
    if (v2 < 10){      
      musicTone();
    }  
    Serial.println("{");
    Serial.println(v2);
    Serial.println("v");
}

static void musicTone() {  
    delay(2000);
    tone(buser,262,200); //DO
    delay(200);
    tone(buser,294,300); //RE
    delay(200);
}
