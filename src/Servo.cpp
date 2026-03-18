#include "Servo.h"
#include <Arduino.h>

int angle = 0;

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

