// Pin definitions
#include "src/Config.h"    
#include "src/Motors.h" 
#include "src/Sensors.h"    
#include "src/Led.h"  
#include <Servo.h>          

Servo scanServo;              

void setup() {
  initMotors();     
  initSensors();    
  initLed();
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  scanServo.attach(SERVO);           
  scanServo.write(90);               
  while (digitalRead(BUTTON_PIN) == HIGH); 
  
  delay(500);
  
  ledOn(CRGB::Green);
}

void loop() {
  int distance = getDistance();

  // 1. Wall Detection
  if (distance > 0 && distance < DISTANCE_THRESHOLD) {
    stopMotors();
    ledOn(CRGB::Red);
    while(true); 
  }

  // 2. Middle Sensor 90 degeree truen
  if (analogRead(SENSOR_M) < LINE_THRESHOLD) {
    turn90();
    delay(200);
  }
  // 3. RIGHT Sensor veer LEFT
  else if (analogRead(SENSOR_R) < LINE_THRESHOLD) {
    veerLeft();
  }
  // 4. LEFT Sensor veer RIGHT
  else if (analogRead(SENSOR_L) < LINE_THRESHOLD) {
    veerRight();
  }
  // 5. Normal
  else {
    goStraight();
  }
}