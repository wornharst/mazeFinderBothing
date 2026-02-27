#include "src/Config.h"
#include "src/Motors.h"
#include "src/Sensors.h"
#include <Servo.h>

// Pins
#define NUM_LEDS 2
#define PIN_RBGLED 4             

// Movement Settings
#define SPEED_LEFT 43     
#define SPEED_RIGHT 40     
#define SPEED_TURN 70       
#define DISTANCE_THRESHOLD 5
#define TURN_TIME 1100
#define CORRECTION_TIME 50 

CRGB leds[NUM_LEDS];          
Servo scanServo;              

void setup() {
  FastLED.addLeds<NEOPIXEL, PIN_RBGLED>(leds, NUM_LEDS);
  
  pinMode(PWR_R, OUTPUT); pinMode(PWR_L, OUTPUT);
  pinMode(MTR_L, OUTPUT); pinMode(MTR_R, OUTPUT);
  pinMode(MTR_ENABLE, OUTPUT);
  pinMode(US_OUT, OUTPUT); pinMode(US_IN, INPUT);
  pinMode(2, INPUT_PULLUP); // Start button
  
  digitalWrite(MTR_ENABLE, HIGH);
  scanServo.attach(SERVO);
  scanServo.write(90); 
  
  // Wait for button press to start
  while (digitalRead(2) == HIGH); 
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

  // 2. Middle Sensor 90 degeree turn
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

void ledOn(CRGB color) {
  leds[0] = color; 
  leds[1] = color; 
  FastLED.show(); 
}