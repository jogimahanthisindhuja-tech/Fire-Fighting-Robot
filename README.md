# Description
This project is an Arduino-based Fire Fighting Robot designed to detect and extinguish fire automatically. It uses flame sensors to identify the presence and direction of fire, navigates toward it, and activates a water pump system to suppress the flames.
The robot also includes a Bluetooth control system, allowing manual operation when needed. This project demonstrates real-time interaction between sensors, actuators, and wireless communication.
# Objectives
- To design a robot capable of detecting fire
- To automatically move toward the fire source
- To extinguish fire using a water spraying mechanism
- To enable manual control using Bluetooth
- To demonstrate embedded system integration
# System Architecture
 The robot consists of the following subsystems:
1. Sensing Unit
- Three flame sensors (Left, Center, Right)
- Detect fire intensity and direction
2. Control Unit
- Arduino microcontroller
- Processes sensor data and executes logic
3. Motion Unit
- DC motors with motor driver
- Enables movement (forward, backward, turning)
4. Extinguishing Unit
- Water pump
- Servo motor for directional spraying
5. Communication Unit
- Bluetooth module (HC-05/HC-06)
- Allows remote control via smartphone
# Components Used
- Arduino UNO
- Flame Sensors (3x)
- L298N Motor Driver
- DC Motors (2x)
- Servo Motor
- Water Pump + Pipe
- Bluetooth Module (HC-05/HC-06)
- Battery Pack
- Robot Chassis
# Pin Configuration
| Component        | Arduino Pin |
|-----------------|------------|
| Motor1 IN1      | 8          |
| Motor1 IN2      | 9          |
| Motor2 IN1      | 10         |
| Motor2 IN2      | 11         |
| Flame Left      | A0         |
| Flame Center    | A1         |
| Flame Right     | A2         |
| Servo Motor     | 6          |
| Pump            | 7          |
| Bluetooth RX    | 2          |
| Bluetooth TX    | 3          |

# Working Principle
-  Automatic Mode
1.Flame sensors continuously monitor surroundings
2.When fire is detected:
Sensor values drop below threshold
3.Robot determines direction:
Center → Move forward
Left → Turn left
Right → Turn right
4.Robot moves toward fire
5.Stops near fire
6.Activates pump and sprays water using servo motion
-  Manual Mode
1.Controlled via Bluetooth commands from mobile
2.User can:
- Move robot in all directions
- Stop movement
- Switch between modes
  

 # Bluetooth commands
 | Command | Function        |
|--------|----------------|
| F      | Move Forward   |
| B      | Move Backward  |
| L      | Turn Left      |
| R      | Turn Right     |
| S      | Stop           |
| M      | Manual Mode    |
| A      | Automatic Mode |
# Fire Extinguishing Mechanism
- A water pump is activated when fire is detected
- Servo motor rotates to spread water over a wider area
- Ensures effective extinguishing
# Algorithm (Logic Flow)
- Start system
- Read flame sensor values
- Check Bluetooth input
- If manual mode → execute user commands
- If automatic mode:
- 
2.Identify direction <br>
3.Move toward fire <br>
4.Stop and spray water <br>
- Repeat continuously <br>
# Setup Instructions
1.Assemble robot chassis and mount components <br>
2.Connect all components as per pin configuration <br>
3.Upload code using Arduino IDE <br>
4.Pair Bluetooth module with smartphone <br>
5.Use any Bluetooth controller app <br>
6.Power the robot <br>
