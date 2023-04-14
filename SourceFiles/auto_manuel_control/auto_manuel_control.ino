#include <SoftwareSerial.h>

//Motor 1
const int motor_1_pin_1  = 6;
const int motor_1_pin_2  = 9;
//Motor 2
const int motor_2_pin_1  = 10;
const int motor_2_pin_2  = 11;

//Auto Taster
const int taster_pin = 12;
bool m_auto = true;
int m_left_right = false;
int count_taster_state = 0;
bool robo_in_air = false;

//Bluetooth
SoftwareSerial hc06(2,3);
char var;

//Vari
int speed = 25.5 * 75;
char blueToothVal;

void setup() {
  //Motor 1
  pinMode(motor_1_pin_1, OUTPUT);
  pinMode(motor_1_pin_2, OUTPUT);
  //Motor 2
  pinMode(motor_2_pin_1, OUTPUT);
  pinMode(motor_2_pin_2, OUTPUT);
  // Auto Taster
  pinMode(taster_pin, INPUT);
  //Bluetooth
  hc06.begin(9600);
  //help
  Serial.begin(9600);  //serieller Monitor wird gestartet, Baudrate auf 9600 festgelegt
}

void loop() {
  if (m_auto){
     // Robo in air
    speed = 190;
    if (digitalRead(taster_pin) == HIGH){  
      count_taster_state = count_taster_state + 1;
      if ( 2 < count_taster_state < 6 ){
        speed = 100;}
      if (count_taster_state > 6){
        speed = 190;
        TurnDirection();
        count_taster_state = 0;
      }
    }
    else {
      Serial.println("auto drive forward");
      count_taster_state = 0;
      Forward('F');
    }
  }
     


  //New Bluetooth Signal
  if (hc06.available()){  // turn true as soon as an value is send
    //set speed
    var = hc06.read();
    if (m_auto == false){
      if (isdigit(var)){
        speed = 25.5 * var;
      }
      else if ( var == 'q'){
        speed = 255;
      }
    }
    else if ( var == 'X'){
      m_auto = false;
      Stop();  
    }
    else if ( var == 'x'){
      m_auto = true;}
    else if ( var == 'F' or var =='G' or var == 'I'){
      Forward(var);} 
    else if ( var == 'B' or var =='H' or var == 'J'){
      Backward(var);}
    else if ( var == 'L'){
      TurnLeft(); }
    else if ( var == 'R'){
      TurnRight();}
    else if ( var == 'S'){
      Stop();}
  }
  delay(50);
  Serial.println(m_auto);
}

void Forward(char direct) {
  if (direct =='G'){
      analogWrite(motor_1_pin_1, 100);
      analogWrite(motor_1_pin_2, 0);
      analogWrite(motor_2_pin_1, 0);
      analogWrite(motor_2_pin_2, speed*0.7); 
  }
  else if (direct =='I'){
    analogWrite(motor_1_pin_1, 0);
    analogWrite(motor_1_pin_2, speed*0.7);
    analogWrite(motor_2_pin_1, 100);
    analogWrite(motor_2_pin_2, 0); 
  }
  else {
    analogWrite(motor_1_pin_1, 0);
    analogWrite(motor_1_pin_2, speed);
    analogWrite(motor_2_pin_1, 0);
    analogWrite(motor_2_pin_2, speed); 
  }
}  

void Backward(char direct) {
  if (direct =='H'){
    analogWrite(motor_1_pin_1, 0);
    analogWrite(motor_1_pin_2, 100);
    analogWrite(motor_2_pin_1, speed*0.7);
    analogWrite(motor_2_pin_2, 0); 
  }
  else if (direct =='J'){
    analogWrite(motor_1_pin_1, speed*0.7);
    analogWrite(motor_1_pin_2, 0);
    analogWrite(motor_2_pin_1, 0);
    analogWrite(motor_2_pin_2, 100); 
  }
  else {
    analogWrite(motor_1_pin_1, speed);
    analogWrite(motor_1_pin_2, 0);
    analogWrite(motor_2_pin_1, speed);
    analogWrite(motor_2_pin_2, 0); 
  }
} 

void TurnDirection() {
  Serial.println("trun start");
  Stop();
  delay(500);
  Backward('B');
  delay(1000);
  if (random(0,2)==1){
    TurnRight();}
  else{
    TurnLeft();
  }
  delay(random(1000,4000));
  Stop();
  delay(500);
  Serial.println("trun stop");
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
