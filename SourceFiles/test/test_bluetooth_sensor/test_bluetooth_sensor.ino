#include <SoftwareSerial.h>

SoftwareSerial hc06(2,3);
char var;

void setup(){
  //Initialize Serial Monitor
  //Initialize Bluetooth Serial Port
  hc06.begin(9600);
  Serial.begin(9600);
  //pinMode(7, OUTPUT);
  //digitalWrite(7, LOW);
  //pinMode(8, OUTPUT);
  //digitalWrite(8, LOW);
  //Serial.println("ENTER AT Commands:");

  
  
}

void loop(){
  //Write data from HC06 to Serial Monitor
  if (hc06.available()){
    var = hc06.read();
    // Serial.println( isdigit(var));
    Serial.println(var);

    delay(50);
  }
  
}
  
