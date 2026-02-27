# Maze Finder Bot
Using c++, we created a Robot that can navigate mazes. 

# Build Instructions

1. Clone the repository
git clone https://github.com/wornharst/mazeFinderBothing.git

2. Open the Robot.ino file in arduino IDE
   
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
- Customizable Wheel Speed: Speed controls for straights (SPEED_LEFT/SPEED_RIGHT) and turns (SPEED_TURN) to compensate for motor variance.

# Project Structure
```
RobotProject/
├── src/
│   ├── Config.h       # Pin definitions and speed constants
│   ├── Motors.h       # Declaration of movement functions
│   ├── Motors.cpp     # Implementation of movement logic
│   ├── Sensors.h      # Declaration of sensor functions
│   └── Sensors.cpp    # Implementation of distance/line logic
├── .gitignore         # Ignore /build or temp files
├── README.md          # Documentation (The text I wrote first)
└── Robot.ino          # Main entry (Setup and Loop)
```

