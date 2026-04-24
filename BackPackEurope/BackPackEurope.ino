#include "Config.h"    
#include "Motors.h" 
#include "Sensors.h"    
#include "Led.h"  
#include "Gyro.h"
#include "Servo.h"
#include <Servo.h>     
#include <Wire.h>   

int sequence[50];       
int currentLevel = 1;   

enum ColorZone { YELLOW_ZONE, BLUE_ZONE, GREEN_ZONE, RED_ZONE };

void setup() {
  initMotors();     
  initSensors();    
  initLed();
  initServo();
  pinMode(BUTTON_PIN, INPUT_PULLUP);             

  Serial.begin(9600);

  ledOn(CRGB::White);
  while (digitalRead(BUTTON_PIN) == HIGH); 
  delay(500);
  ledOn(CRGB::Black); 

  if (!setupGyro()) {
    ledOn(CRGB::Red);
    while (true);  
  }  

  calibrateGyro();
  randomSeed(analogRead(0)); 
  delay(1000);
}

void loop() {
  // 1. Add new random color (0 to 3) to the sequence
  sequence[currentLevel - 1] = random(0, 4); 

  // PHASE 1: DISPLAY THE SEQUENCE

  for (int i = 0; i < currentLevel; i++) {
    int colorToShow = sequence[i];

    if (colorToShow == YELLOW_ZONE) ledOn(CRGB::Yellow);
    else if (colorToShow == BLUE_ZONE) ledOn(CRGB::Blue);
    else if (colorToShow == GREEN_ZONE) ledOn(CRGB::Green);
    else if (colorToShow == RED_ZONE) ledOn(CRGB::Red);

    delay(1000); 

    ledOn(CRGB::Black); 
    delay(500);
  }

  // PHASE 2: REPRODUCTION

  for (int i = 0; i < currentLevel; i++) {
    int targetColor = sequence[i];

    ledOn(CRGB::Black);


    unsigned long startTime = millis();
    while (millis() - startTime < 5000) {
      updateGyroAngle(); 
    }

    int currentAngle = getAngle();
    bool isCorrect = false;
    Serial.println(currentAngle);
    
    if (targetColor == YELLOW_ZONE && currentAngle >= 0 && currentAngle <= 90) {
      isCorrect = true;
    } else if (targetColor == BLUE_ZONE && currentAngle >= 91 && currentAngle <= 180) {
      isCorrect = true;
    } else if (targetColor == GREEN_ZONE && currentAngle <= -1 && currentAngle >= -90) {
      isCorrect = true;
    } else if (targetColor == RED_ZONE && currentAngle <= -91 && currentAngle >= -180) {
      isCorrect = true;
    }

    // GAME OVER
    if (!isCorrect) {
      ledOn(CRGB::White); 
      digitalWrite(MTR_L, HIGH); 
      digitalWrite(MTR_R, HIGH);
      analogWrite(PWR_L, 200);
      analogWrite(PWR_R, 200);
      while (true);
    }

    // Flash purple ONLY if its the LAST color in the sequence
    if (i == currentLevel - 1) {
      ledOn(CRGB::Purple);
      delay(3000); 
    }

    ledOn(CRGB::Black); 
    delay(500); 

    updateGyroAngle();
    currentAngle = getAngle();
    
    while (currentAngle > 5) {
      digitalWrite(MTR_L, HIGH);  
      digitalWrite(MTR_R, LOW);  
      analogWrite(PWR_L, SPEED_TURN - 20); 
      analogWrite(PWR_R, SPEED_TURN - 20);
      
      updateGyroAngle();
      currentAngle = getAngle();
    }

    while (currentAngle < -5) {
      digitalWrite(MTR_L, LOW);  
      digitalWrite(MTR_R, HIGH);   
      analogWrite(PWR_L, SPEED_TURN - 20);
      analogWrite(PWR_R, SPEED_TURN - 20);
      
      updateGyroAngle();
      currentAngle = getAngle();
    }

    stopMotors();
    delay(500); 

    resetAngle(); 
    delay(500);
  }

  currentLevel++;
  delay(1000); 
}