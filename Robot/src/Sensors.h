#ifndef SENSORS_H
#define SENSORS_H

#include "Config.h"

void initSensors();
int getDistance();
bool checkLine(int sensorPin);

#endif