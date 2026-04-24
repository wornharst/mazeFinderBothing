#include "Sensors.h"
#include <Arduino.h>

void initSensors() {
    pinMode(US_OUT, OUTPUT); 
    pinMode(US_IN, INPUT);
}

int getDistance() {
    digitalWrite(US_OUT, LOW); delayMicroseconds(2);
    digitalWrite(US_OUT, HIGH); delayMicroseconds(10);
    digitalWrite(US_OUT, LOW);
    long duration = pulseIn(US_IN, HIGH, 30000);
    int d = duration * 0.034 / 2;
    return (d == 0 || d > 200) ? 0 : d;
}