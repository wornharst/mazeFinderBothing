#include "Motors.h"
#include "Led.h"
#include "Gyro.h"
#include <Arduino.h>

void initMotors() {
    pinMode(PWR_R, OUTPUT); pinMode(PWR_L, OUTPUT);
    pinMode(MTR_L, OUTPUT); pinMode(MTR_R, OUTPUT);
    pinMode(MTR_ENABLE, OUTPUT);
    digitalWrite(MTR_ENABLE, HIGH);
}

void goStraight() {
    digitalWrite(MTR_L, HIGH); digitalWrite(MTR_R, HIGH);
    analogWrite(PWR_L, SPEED_LEFT); analogWrite(PWR_R, SPEED_RIGHT);
}

void stopMotors() {
    analogWrite(PWR_L, 0); analogWrite(PWR_R, 0);
}

void veerLeft() {
  ledOn(CRGB::Blue);
  digitalWrite(MTR_L, LOW); 
  digitalWrite(MTR_R, HIGH);
  analogWrite(PWR_L, SPEED_LEFT);
  analogWrite(PWR_R, SPEED_RIGHT); 
  delay(CORRECTION_TIME);
  ledOn(CRGB::Green);
}

void veerRight() {
  ledOn(CRGB::Blue);
  digitalWrite(MTR_L, HIGH);
  digitalWrite(MTR_R, LOW); 
  analogWrite(PWR_L, SPEED_LEFT); 
  analogWrite(PWR_R, SPEED_RIGHT);
  delay(CORRECTION_TIME);
  ledOn(CRGB::Green);
}

void turnLeft(int targetAngle) {
  updateGyroAngle();
  int angle = getAngle();

  while(abs(angle) < targetAngle) {
    digitalWrite(MTR_L, HIGH);   
    digitalWrite(MTR_R, LOW); 
    analogWrite(PWR_L, SPEED_TURN);
    analogWrite(PWR_R, SPEED_TURN);
    updateGyroAngle();
    angle = getAngle();
  }
  stopMotors();
}

void turnRight(int targetAngle) {
  updateGyroAngle();
  int angle = getAngle();

  while(abs(angle) < targetAngle) {
    digitalWrite(MTR_L, LOW); 
    digitalWrite(MTR_R, HIGH); 
    analogWrite(PWR_L, SPEED_TURN);
    analogWrite(PWR_R, SPEED_TURN);
    updateGyroAngle();
    angle = getAngle();
  }
  stopMotors();
}

void doStupidDance(){
  resetAngle();
  turnRight(20);
  delay(100);
  turnLeft(20);
  delay(100);
  turnRight(20);
  delay(100);
  turnLeft(20);
  delay(100);
  turnRight(20);
  delay(100);
  turnLeft(179);
  resetAngle();

  turnRight(20);
  delay(100);
  turnLeft(20);
  delay(100);
  turnRight(20);
  delay(100);
  turnLeft(20);
  delay(100);
  turnRight(20);
  delay(100);
  turnLeft(179);
  resetAngle();

  turnLeft(20);
  delay(100);
  turnRight(20);
  delay(100);
  turnLeft(20);
  delay(100);
  turnRight(20);
  delay(100);
  turnLeft(20);
  delay(100);
  turnRight(179);
  resetAngle();

  turnLeft(20);
  delay(100);
  turnRight(20);
  delay(100);
  turnLeft(20);
  delay(100);
  turnRight(20);
  delay(100);
  turnLeft(20);
  delay(100);
  turnRight(179);
  resetAngle();

  turnRight(20);
  delay(100);
  turnLeft(20);
  delay(100);
  turnRight(20);
  delay(100);
  turnLeft(20);
  delay(100);
  turnRight(20);
  delay(100);
  turnLeft(20);
  resetAngle();
}
