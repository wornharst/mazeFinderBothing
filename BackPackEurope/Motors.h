#ifndef MOTORS_H
#define MOTORS_H

#include "Config.h"

void initMotors();
void goStraight();
void veerLeft();
void veerRight();
void turnLeft(int targetAngle);
void turnRight(int targetAngle);
void stopMotors();

#endif