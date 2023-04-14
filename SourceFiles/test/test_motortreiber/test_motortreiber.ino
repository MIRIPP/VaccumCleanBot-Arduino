//Motor 1
const int motorPin1  = 6;
const int motorPin2  = 9;
//Motor 2
const int motorPin3  = 10;
const int motorPin4  = 11;

int speed = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  


}

void loop() {
  // put your main code here, to run repeatedly:
    //Motor Control A in both directions
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, 0);
  analogWrite(motorPin3, 0);
  analogWrite(motorPin4, 0);
  
  analogWrite(motorPin1, speed);
  delay(2000);
  analogWrite(motorPin1, 0);
  delay(200);
  analogWrite(motorPin2, speed);
  delay(2000);
  analogWrite(motorPin2, 0);
  //Motor Control B in both directions
  
  analogWrite(motorPin3, speed);
  delay(2000);
  analogWrite(motorPin3, 0);
  delay(200);
  analogWrite(motorPin4, speed);
  delay(2000);
  analogWrite(motorPin4, 0);


}
