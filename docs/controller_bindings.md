/**
 * @file controller.cpp
 * @brief This file contains the implementation of the controller functionalities for the robot.
 *
 * The controller functionalities include handling the main and partner controllers, switching control between them,
 * and providing feedback to the driver about the state of the robot and its components.
 *

## Main Controller Controls

Based on the type of drive as well as the program orientation of the robot, the joysticks on the 
- **Left Joystick (Vertical Axis)**: Controls the forward and backward movement of the robot.
- **Right Joystick (Horizontal Axis)**: Controls the left and right movement (turning) of the robot.


- **R1 Button**: Activates the intake motor to pull in objects.
- **L1 Button**: Activates the intake motor to push out objects.
- **Digital Up Button**: Toggles the drivetrain orientation (forward or backward).
- **Digital Down Button**: Executes the autonomous routine during user control.
- **Digital Right Button**: Toggles the drivetrain reversal.
- **Digital Left Button**: Reserved for future use.
- **L2 Button**: Switches control between the main and partner controllers if the partner controller is connected.
## Partner Controller Controls
- **Digital Y Button**: Sends a rumble pattern "..-" to the main controller.
- **Digital X Button**: Sends a rumble pattern ".-." to the main controller.
- **Digital Up Button**: Sends a rumble pattern "-.." to the main controller.
- **Digital Right Button**: Sends a rumble pattern "-.-" to the main controller.
- **Digital R1 Button**: Sends a rumble pattern "..." to the main controller to notify of only 15 seconds remaining.
## Additional Functionalities
- **Motor Disconnect Notification**: The main controller provides haptic and visual feedback if a motor disconnects or reconnects.
  - Three short pulses indicate a motor disconnect.
  - One long pulse indicates a motor reconnect.
  - The LCD screen on the controller displays the current disconnected motors.
