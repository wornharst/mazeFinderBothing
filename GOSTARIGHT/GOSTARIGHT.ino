#include "Config.h"    
#include "Motors.h" 
#include "Sensors.h"    
#include "Led.h"  
#include <Servo.h>     
#include <Wire.h>               

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

  if (!setupGyro()) {
    ledOn(CRGB::Red);
    while (true);  // Hard stop
  }  

  calibrateGyro();
}

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

  Serial.println(distance);

  delay(200);

}


void setServoAngle(int angle) {
  static int lastAngle = -1;
  angle = constrain(angle, 0, 180);

  if (angle != lastAngle) {
    scanServo.write(angle);
    delay(15);  // Allow servo to settle
    lastAngle = angle;
  }
}


// Center the servo
void centerServo() {
  setServoAngle(90);
}

