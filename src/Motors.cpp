#include "Motors.h"
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

// ... Add veerLeft, veerRight, and turn90 here from your original code ...