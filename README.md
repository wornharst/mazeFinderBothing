# Maze Finder Bot
Using c++, we created a Robot that can navigate mazes. 

# build instructions

1. Clone the repository
git clone https://github.com/wornharst/mazeFinderBothing.git

2. Open the Robot.ino file in arduino IDE
   
3. Upload and Press button on robot. 

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
Calendar/
├── .vscode/
│   └── tasks.json             # Automation tasks for building the project
├── database/
│   └── calander project.exe   # Main application executable
├── ui/
│   ├── SDL3.dll               # Dynamic Link Library required for graphics
│   ├── userWindow.cpp         # Source code for the UI implementation
│   └── userWindow.exe         # Executable for UI testing
├── .gitignore                 # Instructions for Git to ignore binary files
├── calender_project.cpp       # Main entry point for the application
└── README.md                  # Project documentation
```

