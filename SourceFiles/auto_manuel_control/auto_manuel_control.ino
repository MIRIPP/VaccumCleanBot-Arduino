#include <SoftwareSerial.h>

//Motor 1
const int motor_1_pin_1 = 6;
const int motor_1_pin_2 = 9;
//Motor 2
const int motor_2_pin_1 = 10;
const int motor_2_pin_2 = 11;

// Motor Hall Sensors
const int hallSensorPin1 = 7;  // Analog pin for Hall sensor 1
const int hallSensorPin2 = 8;  // Analog pin for Hall sensor 2
int count_hall_sensor1 = 0;
int count_hall_sensor2 = 0;
bool safed_hall_sensor_state1 = false;
bool safed_hall_sensor_state2 = false;

//Auto Taster
const int taster_pin = 12;
int count_taster_state = 0;

//Bluetooth
SoftwareSerial hc06(2, 3);
char var;

//Vari
int speed = 25.5 * 7;  // speed from 0-10, defautl is 5 // 0..255
int speed_manual_setting = 0;
bool m_auto = true;



void setup() {
  //Motor 1
  pinMode(motor_1_pin_1, OUTPUT);
  pinMode(motor_1_pin_2, OUTPUT);
  //Motor 2
  pinMode(motor_2_pin_1, OUTPUT);
  pinMode(motor_2_pin_2, OUTPUT);
  // Auto Taster
  pinMode(taster_pin, INPUT);
  // Motor hall Sensors
  pinMode(hallSensorPin1, INPUT);
  pinMode(hallSensorPin2, INPUT);
  //Bluetooth
  hc06.begin(9600);
  //help
  Serial.begin(9600);  //serieller Monitor wird gestartet, Baudrate auf 9600 festgelegt
}

void loop() {
  if (m_auto) {

    // motor 1 might stuck
    bool current_sensor_state1 = digitalRead(hallSensorPin1) == LOW;
    if (current_sensor_state1 == safed_hall_sensor_state1) {
      count_hall_sensor1 = count_hall_sensor1 + 1;
    } else {
      count_hall_sensor1 = 0;
      safed_hall_sensor_state1 = current_sensor_state1;
    }
    // motor 2 might stuck
    bool current_sensor_state2 = digitalRead(hallSensorPin2) == LOW;
    if (current_sensor_state2 == safed_hall_sensor_state1) {
      count_hall_sensor2 = count_hall_sensor2 + 1;
    } else {
      count_hall_sensor2 = 0;
      safed_hall_sensor_state2 = current_sensor_state2;
    }
    // Robo might in air
    if (digitalRead(taster_pin) == HIGH) {
      count_taster_state = count_taster_state + 1;  // taster have to be high for 6 times befor we take action
      if (2 < count_taster_state < 6) {
        speed = 100;  // slow down
      }
    } else {
      count_taster_state = 0;
    }

    // Robo REALY in air or stuck
    if (count_taster_state > 6 || (count_hall_sensor1 > 20) || (count_hall_sensor2 > 20)) {
      Serial.println("Robo in air or stuck");
      speed = 190;  // turn speed
      TurnDirection();
      count_taster_state = 0;
      count_hall_sensor1 = 0;
      count_hall_sensor2 = 0;
    } else {
      if (speed_manual_setting > 0) {
        speed = speed_manual_setting;
      } else {
        speed = 190;
      }
      Forward('F');
    }
  }

  //New Bluetooth Signal
  if (hc06.available()) {  // turn true as soon as an value is send
    //Serial.println("hc06.available: true");
    var = hc06.read();
    Serial.println(var);
    if (isdigit(var)) {
      int intVar = atoi(&var);
      speed = 128 + (13 * intVar);  //128 = minimum speed, 13 = 128/10 stepsiez, 255 = max speed, var: 0-10
      speed_manual_setting = 128 + (13 * intVar);
      Serial.println(speed);
    } else if (var == 'q') {
      speed = 255;
      speed_manual_setting = 255;
    } else if (var == 'X') {
      m_auto = false;
      Serial.println("Bluetooth Mode");
      Stop();
    } else if (var == 'x') {
      m_auto = true;
      Serial.println("auto Mode");
    } else if (var == 'F' or var == 'G' or var == 'I') {
      Forward(var);
    } else if (var == 'B' or var == 'H' or var == 'J') {
      Backward(var);
    } else if (var == 'L') {
      TurnLeft();
    } else if (var == 'R') {
      TurnRight();
    } else if (var == 'S') {
      Stop();
    }
  }
  delay(50);
}

void Forward(char direct) {
  Serial.println("drive Forward");
  if (direct == 'G') {
    analogWrite(motor_1_pin_1, 100);  // need to be at least 100 otherwise the motor stops
    analogWrite(motor_1_pin_2, 0);
    analogWrite(motor_2_pin_1, 0);
    analogWrite(motor_2_pin_2, speed * 0.7);
  } else if (direct == 'I') {
    analogWrite(motor_1_pin_1, 0);
    analogWrite(motor_1_pin_2, speed * 0.7);
    analogWrite(motor_2_pin_1, 100);
    analogWrite(motor_2_pin_2, 0);
  } else {
    analogWrite(motor_1_pin_1, 0);
    analogWrite(motor_1_pin_2, speed);
    analogWrite(motor_2_pin_1, 0);
    analogWrite(motor_2_pin_2, speed);
  }
}

void Backward(char direct) {
  Serial.println("drive Backward");
  if (direct == 'H') {
    analogWrite(motor_1_pin_1, 0);
    analogWrite(motor_1_pin_2, 100);
    analogWrite(motor_2_pin_1, speed * 0.7);
    analogWrite(motor_2_pin_2, 0);
  } else if (direct == 'J') {
    analogWrite(motor_1_pin_1, speed * 0.7);
    analogWrite(motor_1_pin_2, 0);
    analogWrite(motor_2_pin_1, 0);
    analogWrite(motor_2_pin_2, 100);
  } else {
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
  if (random(0, 2) == 1) {
    TurnRight();
  } else {
    TurnLeft();
  }
  delay(random(1000, 4000));
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
