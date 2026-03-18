#include "Config.h"    
#include "Motors.h" 
#include "Sensors.h"    
#include "Led.h"  
#include <Servo.h>          

Servo scanServo;              

void setup() {
  //pin definitions
  initMotors();     
  initSensors();    
  initLed();
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  scanServo.attach(SERVO);           
  scanServo.write(90);               

  while (digitalRead(BUTTON_PIN) == HIGH); 
  delay(500);
  ledOn(CRGB::Green);
  Serial.begin(9600);
}
int turnAmount;

void loop() {
  int middle = analogRead(SENSOR_M);
  int right = analogRead(SENSOR_R);
  int left = analogRead(SENSOR_L);

  int distance = getDistance();

  if (analogRead(SENSOR_M) > LINE_THRESHOLD) {
    if (turnAmount < 4){
      turnRight90();
      turnAmount +=1;
      Serial.print(turnAmount);
    }

    if (turnAmount >= 4 && analogRead(SENSOR_M) > LINE_THRESHOLD){
      turnLeft90();
      turnAmount = 0;
    }
  }

  else{
    goStraight();
  }
}