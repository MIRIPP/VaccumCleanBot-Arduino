# ArduinoVaccumCleanBot
This project involves building a vacuum cleaner robot that can be controlled manually via an Android app connected via Bluetooth or can operate autonomously. The robot will be equipped with obstacle detection sensors.

In manual mode, the user can control the robot's movement and direction using the Android app, which sends signals to the Arduino board to control the motors. The app will include various functions such as forward, backward, left turn, right turn, and stop.

In autonomous mode, the robot will navigate around the room by driving straight until it detects an obstacle. When it detects an obstacle, the robot will stop, then he will move in a random direction until it encounters another obstacle and repeats the process.

## Getting Started

- Wire the components like shown in the Wiring Diagram
- Upload the code to your Arduino board
- Install the "Bluetooth RC Controller" App on your Phone (only for manual driving)
- Connect your Phone via Bluetooth to the HC05 Moduel  (only for manual driving)


## Wiring Diagram

https://github.com/MIRIPP/ArduinoVaccumCleanBot/blob/main/doc/schaltplan%20bluetooth.png?raw=true

## Hardware List

- Arduino Board (e.g. Arduino Uno, Arduino Mega, etc.)
- List of other required hardware components (e.g. sensors, motors, etc.)

Feel free to add any additional information, instructions, or acknowledgements as necessary. Good luck with your project!
