# Rover AI

**Smart Mars Rover** — a capstone project combining Q-learning, Arduino
hardware, and (eventually) computer vision to build an autonomous
obstacle-avoiding rover.

## Project Goal

Build a miniature rover that senses its environment, makes navigation
decisions using reinforcement learning, and physically avoids obstacles —
as a hands-on foundation for aerospace/autonomous-systems engineering.

## Repository Structure
Rover-AI/
├── arduino/     # Arduino sketches (obstacle avoidance, motor control)
├── python/      # Q-learning simulation code
├── docs/        # Project reports, PPT outline, planning documents
└── README.md
## Current Status

- ✅ Basic obstacle-avoidance logic running on Arduino (ultrasonic sensor + motor driver)
- ✅ Tabular Q-learning implemented in Python (simulation only, not yet connected to hardware)
- 🔄 In progress: engineering math (sensor geometry, navigation vectors), GitHub structure
- ⏳ Planned: serial link between Python Q-learning and Arduino, computer vision integration

## Hardware Used

- Arduino UNO
- HC-SR04 Ultrasonic Sensor
- L298N Motor Driver
- 2x DC Motors + Chassis
- Battery Pack (12V motors / 5V logic)

## Software Used

- Arduino IDE (C++)
- Python 3 (NumPy, planned: PySerial, OpenCV)
- Git / GitHub for version control

## Author

Kamesh — self-directed engineering study toward aerospace/autonomous systems.