#include "Config.h"    
#include "Motors.h" 
#include "Sensors.h"    
#include "Led.h"  
#include "Gyro.h"
#include "Servo.h"
#include <Servo.h>     
#include <Wire.h>   

void setup() {
  //pin definitions
  initMotors();     
  initSensors();    
  initLed();
  initServo();
  pinMode(BUTTON_PIN, INPUT_PULLUP);             

  while (digitalRead(BUTTON_PIN) == HIGH); 
  delay(500);
  ledOn(CRGB::Green);
  Serial.begin(9600);

  if (!setupGyro()) {
    ledOn(CRGB::Red);
    while (true);  // Hard stop
  }  

  calibrateGyro();
}

int angle = 0;

void loop() {
  int distance = getDistance();
  Serial.println(distance);
  updateGyroAngle();
  angle = getAngle();

  if(angle > 0){
    veerLeft();
    delay(50);
  }

  if(angle < 0){
    veerRight();
    delay(50);
  }
}

