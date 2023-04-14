#include <SoftwareSerial.h>

//Motor 1
const int motor_1_pin_1  = 6;
const int motor_1_pin_2  = 9;
const int motor_1_sensor_1  = 4;
const int motor_1_sensor_2  = 5;
//Motor 2
const int motor_2_pin_1  = 10;
const int motor_2_pin_2  = 11;
const int motor_2_sensor_1  = 7;
const int motor_2_sensor_2  = 8;
//Ultraschallsensoren
//const int sensor_front  = 1;
//const int sensor_left  = 2;
//const int sensor_right  = 12;
//const int sensor_check  = 13;
//Bluetooth
SoftwareSerial hc06(2,3);
char var;
//Vari
int speed = 100;
char blueToothVal;

void setup() {
  //Motor 1
  pinMode(motor_1_pin_1, OUTPUT);
  pinMode(motor_1_pin_2, OUTPUT);
  pinMode(motor_1_sensor_1, INPUT);
  pinMode(motor_1_sensor_2, INPUT);
  //Motor 2
  pinMode(motor_2_pin_1, OUTPUT);
  pinMode(motor_2_pin_2, OUTPUT);
  pinMode(motor_2_sensor_1, INPUT);
  pinMode(motor_2_sensor_2, INPUT);
  //Ultraschallsensoren
//  pinMode(sensor_front, INPUT);
//  pinMode(sensor_left, INPUT);
//  pinMode(sensor_right, INPUT);
//  pinMode(sensor_check, OUTPUT);
  //Bluetooth
  hc06.begin(9600);
  //help
  Serial.begin(9600);  //serieller Monitor wird gestartet, Baudrate auf 9600 festgelegt
}

void loop() {
  if (hc06.available()){
    var = hc06.read();
    if (isdigit(var)){
      speed = 25.5 * var;
    }
    else if ( var == 'q'){
      speed = 255;
    }
    else if ( var == 'F' or var =='G' or var == 'I'){
      Forward(var);
    } 
    else if ( var == 'B' or var =='H' or var == 'J'){
      Backward(var);
    }
    else if ( var == 'L'){
      TurnLeft();
    }
    else if ( var == 'R'){
      TurnRight();
    }
    else if ( var == 'S'){
      Stop();
    }      
      
    delay(50);
  }
}

void Forward(char direct) {
  if (direct =='G'){
    analogWrite(motor_1_pin_2, 0);
    analogWrite(motor_2_pin_2, speed);
  }
  else if (direct =='I'){
    analogWrite(motor_1_pin_2, speed);
    analogWrite(motor_2_pin_2, 0);
  }
  else {
    analogWrite(motor_1_pin_2, speed);
    analogWrite(motor_2_pin_2, speed);
  }
  analogWrite(motor_1_pin_1, 0);
  analogWrite(motor_2_pin_1, 0);
}  

void Backward(char direct) {
  if (direct =='H'){
    analogWrite(motor_1_pin_1, 0);
    analogWrite(motor_2_pin_1, speed);
  }
  else if (direct =='J'){
    analogWrite(motor_1_pin_1, speed);
    analogWrite(motor_2_pin_1, 0);
  }
  else {
    analogWrite(motor_1_pin_1, speed);
    analogWrite(motor_2_pin_1, speed);
  }
  analogWrite(motor_1_pin_2, 0);
  analogWrite(motor_2_pin_2, 0);
} 


void TurnLeft() {
  analogWrite(motor_1_pin_1, speed);
  analogWrite(motor_1_pin_2, 0);
  analogWrite(motor_2_pin_1, 0);
  analogWrite(motor_2_pin_2, speed);  
}

void TurnRight() {
  analogWrite(motor_1_pin_1, 0);
  analogWrite(motor_1_pin_2, speed);
  analogWrite(motor_2_pin_1, speed);
  analogWrite(motor_2_pin_2, 0);  
}

void Stop() {
  analogWrite(motor_1_pin_1, 0);
  analogWrite(motor_1_pin_2, 0);
  analogWrite(motor_2_pin_1, 0);
  analogWrite(motor_2_pin_2, 0);
  
}
