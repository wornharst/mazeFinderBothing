#include "Servo.h"
#include <Servo.h>
#include <Arduino.h>

Servo scanServo;

void initServo() {
  scanServo.attach(SERVO);           
  scanServo.write(90);   
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

