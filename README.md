# Maze Finder Bot
Using c++, we created a Robot that can navigate mazes. 

# Build Instructions

1. Clone the repository
git clone https://github.com/wornharst/mazeFinderBothing.git

2. Open the any of the files in arduino IDE
   
3. Upload and Press button on robot to start it. 

## Description
This project is an Arduino based robot designed to navigate tracks using line-following sensors while looking for obstacles. The robot uses a three sensors on the bottom to track paths and do precise 90-degree turns. It features ultrasonic distance sensing to prevent collisions and provides real time visual feedback via RGB LEDs to indicate its current operational state (moving, turning, or stopped).

### Features
- Intelligent Line Following: Uses 3 sensors (Left, Middle, Right) with a customizable threshold to maintain path alignment.
- Precision Turning: Includes logic for 90-degree turns when the middle sensor detects a line.
- Obstacle Avoidance: Ultrasonic sensor support to detect walls or obstacles.
- Visual Status Indicators: RGB LEDs provide feedback:
  - Green: Go forward.
  - Blue: Path correctio.
  - Purple: 90-degree turn.
  - Red: Obstacle detected.
- Safety Start: Waits for a physical trigger before the robot begins moving.
- Customizable Wheel Speed: Speed controls for straights (SPEED_LEFT/SPEED_RIGHT) and turns (SPEED_TURN) to fix drift.

# Project Structure
```
RobotProject/
├── BackPackEurope/    # Memory Game
├── GOSTRIAGHT/        # Gyro staright file
├── lineTracing/       # Line Follower
├── Robot/             # First Code 
├── WINNERWINNER/      # The Final Maze/Line follow Solver
├── src/
│   ├── Config.h       # Pin definitions and speed constants
│   ├── Motors.h       # Declaration of movement functions
│   ├── Motors.cpp     # Implementation of movement logic
│   ├── Sensors.h      # Declaration of sensor functions
│   ├── Senors.cpp     # Implementation of sensor logic
│   ├── Led.h          # Declaration of led functions
│   ├── Led.cpp        # Implementation of led logic
│   ├── Gyro.h         # Declaration of gyro functions
│   ├── Gyro.cpp       # Implementation of hyro logic
│   ├── Servo.h        # Declaration of servo functions
│   └── Servo.cpp      # Implementation of servo head logic
├── README.md          # Documentation 
```

