#ifndef GYRO_H
#define GYRO_H

#include "Config.h"

void calibrateGyro();
bool setupGyro();
int16_t readGyroZ();
void updateGyroAngle();
void resetAngle();
float getAngle();

#endif