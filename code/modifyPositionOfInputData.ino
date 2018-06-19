// command에 1000이 들어오면 모터를 구동하고, 아니면 1000이 들어올 때까지 자리를 이동  
#include <SoftwareSerial.h>
#include <Servo.h>


int enA = 3;
int in1 = 12; 
int in2 = 9; //brake
int ledRed = 13;
int ledBlue = 7;  

Servo myServo;
int command = 0;
int dir = 0;
int valServo = 90;
int valMotor = 0;

int temp1 = 0;

SoftwareSerial mySerial(6, 5);

void setup() {
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(ledRed, OUTPUT);
  
  myServo.attach(5);
  myServo.write(valServo);
  
  digitalWrite(in1, HIGH);
  analogWrite(enA, valMotor);
  
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  if(mySerial.available()) {
    if(mySerial.read() == '\n') {
      command = mySerial.parseInt();
      dir = mySerial.parseInt();
      valServo = mySerial.parseInt();
      valMotor = mySerial.parseInt();
    }
  }

  if (command != 1000) {     
      temp1 = command;
      command = dir;
      dir = valServo;
      valServo = valMotor;
      dir = temp1;   
      Serial.print("out  "); 
      Serial.print(command);
      Serial.print("  ");  
      Serial.print(dir);
      Serial.print("  ");
      Serial.print(valServo);
      Serial.print("  ");
      Serial.print(valMotor);
      Serial.println("  ");
   } else  {
      Serial.print("in   ");  
      Serial.print(command);
      Serial.print("  ");
      Serial.print(dir);
      Serial.print("  ");
      Serial.print(valServo);
      Serial.print("  ");
      Serial.println(valMotor);
          
    // dir == 1 forward, dir ==2 backward
    if (dir == 1) {
      forwardCar(dir, valServo, valMotor);
    }
    if (dir == 2) {
      backwardCar(dir, valServo, valMotor);
    }
    if (dir == 0) {
      stopCar(valServo);
    }
  }
}       
  


void forwardCar(int dir, int valServo, int valMotor) {
  myServo.write(valServo);
  digitalWrite(ledRed, HIGH);
  digitalWrite(in1, HIGH);
  analogWrite(enA, valMotor);
}

void backwardCar(int dir, int valServo, int valMotor) {
  myServo.write(valServo);
  digitalWrite(ledRed, HIGH);
  digitalWrite(in1, LOW);
  analogWrite(enA, valMotor);
}

void stopCar(int valServo) {
  myServo.write(valServo);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledBlue, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
}
  
