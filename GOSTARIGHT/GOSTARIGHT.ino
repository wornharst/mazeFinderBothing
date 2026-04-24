#include "Config.h"
#include "Motors.h"
#include "Sensors.h"
#include "Led.h"
#include "Gyro.h"
#include "Servo.h"
#include <Servo.h>
#include <Wire.h>

int dance = 0;

void setup() {
  initMotors();
  initSensors();
  initLed();
  initServo();
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);

  ledOn(CRGB::White);
  while (digitalRead(BUTTON_PIN) == HIGH)
    ;
  delay(500);
  ledOn(CRGB::Black);

  if (!setupGyro()) {
    ledOn(CRGB::Red);
    while (true)
      ;
  }

  calibrateGyro();
  delay(1000);
}

void loop() {
  int middle = analogRead(SENSOR_M);
  int right = analogRead(SENSOR_R);
  int left = analogRead(SENSOR_L);

  // --- maze mode ---
  if (middle > LINE && right > LINE && left > LINE) {
    int distance = getDistance();
    
    //if see wall
    if (distance < 3 && distance > 0) { 
      stopMotors();

      //look left
      setServoAngle(0); 
      delay(1000);
      int distRight = getDistance();
      bool rightOpen = (distRight > 25);

      //look right
      setServoAngle(180); 
      delay(1000);
      int distLeft = getDistance();
      bool leftOpen = (distLeft > 25);

      centerServo();

      if (rightOpen && leftOpen) {
        turnLeft(NINTY_DEGREES);
      }
      else if (rightOpen) {
        turnRight(NINTY_DEGREES);
        resetAngle();
        rightTurnCount++; 
      }
      else if (leftOpen) {
        turnLeft(NINTY_DEGREES);
        resetAngle();
      }
      else {
        turnRight(ONE_EIGHTY_DEGREES);
        resetAngle();
      }
    } 
    else {
      goStraight();
    }
  }

  // --- line follow ---
  else if(middle < LINE && right < LINE && left < LINE){

    while(true){
      middle = analogRead(SENSOR_M);
      right = analogRead(SENSOR_R);
      left = analogRead(SENSOR_L);

      //if sensors detect dark line
      if (middle > LINE && right > LINE && left > LINE){
        dance += 1;
        if (dance >= 2){
          doStupidDance();
          while(true){
            stopMotors();
          }
        }
        break;
      }
      
      else if(left > LINE){
        veerLeft();
      }
      else if(right > LINE){
        veerRight();
      }
      else if (middle < LINE){
        goStraight();
      }
    }
  }
}