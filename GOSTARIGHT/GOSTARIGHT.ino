#include "Config.h"    
#include "Motors.h" 
#include "Sensors.h"    
#include "Led.h"  
#include <Servo.h>     
#include <Wire.h>    
#define SERVO 10  
#define GYRO 0x68  

int16_t gyroZ;                // Raw gyro Z-axis reading
float gyroZOffset = 0;        // Calibration offset
float currentAngle = 0;       // Current angle in degrees
int angle = 0;
unsigned long lastTime = 0; 

Servo scanServo;              

void setup() {
  //pin definitions
  initMotors();     
  initSensors();    
  initLed();
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  scanServo.attach(SERVO);           
  scanServo.write(90);               

  while (digitalRead(BUTTON_PIN) == HIGH); 
  delay(500);
  ledOn(CRGB::Green);
  Serial.begin(9600);

  if (!setupGyro()) {
    ledOn(CRGB::Red);
    while (true);  // Hard stop
  }  

  calibrateGyro();
}

void loop() {
  int distance = getDistance();
  Serial.println(distance);
  // updateGyroAngle();
  // angle = getAngle();

  // if(angle > 0){
  //   veerLeft();
  //   delay(50);
  // }

  // if(angle < 0){
  //   veerRight();
  //   delay(50);
  // }

  Serial.println(distance);

  delay(200);

}
















// Initialize Gyro Sensor
bool setupGyro() {
  Wire.begin();
  Wire.beginTransmission(GYRO);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // Wake up MPU6050
  byte error = Wire.endTransmission();
  
  if (error != 0) {
    return false;
  }
  
  // Configure gyro sensitivity (±250 deg/s)
  Wire.beginTransmission(GYRO);
  Wire.write(0x1B);  // GYRO_CONFIG register
  Wire.write(0x00);  // ±250 deg/s
  Wire.endTransmission();
  
  lastTime = millis();
  return true;
}

// Calibrate gyro (robot must be stationary!)
void calibrateGyro() {
  delay(500);
  
  long sum = 0;
  int samples = 100;
  
  for (int i = 0; i < samples; i++) {
    Wire.beginTransmission(GYRO);
    Wire.write(0x47);  // GYRO_ZOUT_H register
    Wire.endTransmission(false);
    Wire.requestFrom(GYRO, 2, true);
    
    int16_t gz = Wire.read() << 8 | Wire.read();
    sum += gz;
    delay(10);
  }
  
  gyroZOffset = sum / samples;
  currentAngle = 0;
}

// Read gyro Z-axis
int16_t readGyroZ() {
  Wire.beginTransmission(GYRO);
  Wire.write(0x47);  // GYRO_ZOUT_H register
  Wire.endTransmission(false);
  Wire.requestFrom(GYRO, 2, true);
  
  int16_t gz = Wire.read() << 8 | Wire.read();
  return gz;
}

// MUST be called frequently (e.g., every loop iteration)
// Angle accuracy degrades if this is not called often
void updateGyroAngle() {
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;  // Time in seconds
  lastTime = now;
  
  // Read gyro
  gyroZ = readGyroZ();
  
  // Convert to degrees per second (sensitivity = 131 for ±250 deg/s)
  // INVERTED THE SIGN HERE to fix direction!
  float gyroRate = -((gyroZ - gyroZOffset) / 131.0);
  
  // Integrate to get angle
  currentAngle += gyroRate * dt;
  
  // Keep angle in range -180 to +180
  if (currentAngle > 180) currentAngle -= 360;
  if (currentAngle < -180) currentAngle += 360;
}

// Reset angle to zero
void resetAngle() {
  currentAngle = 0;
}

// Get current angle
float getAngle() {
  return currentAngle;
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

