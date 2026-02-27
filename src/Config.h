#ifndef CONFIG_H
#define CONFIG_H

#include <FastLED.h>

// Pins
#define NUM_LEDS 2
#define PIN_RBGLED 4
#define PWR_R 5               
#define PWR_L 6               
#define MTR_R 8               
#define MTR_L 7               
#define SERVO 10              
#define MTR_ENABLE 3          
#define US_OUT 13             
#define US_IN 12              

// Sensors
#define SENSOR_L A2
#define SENSOR_M A1
#define SENSOR_R A0
#define LINE_THRESHOLD 500
#define BUTTON_PIN 2

// Movement Settings
#define SPEED_LEFT 43     
#define SPEED_RIGHT 40     
#define SPEED_TURN 70       
#define DISTANCE_THRESHOLD 5
#define TURN_TIME_90 1100
#define CORRECTION_TIME 50 

#endif