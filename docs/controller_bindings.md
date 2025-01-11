/**
 * @file controller.cpp
 * @brief This file contains the implementation of the controller functionalities for the robot.
 *
 * The controller functionalities include handling the main and partner controllers, switching control between them,
 * and providing feedback to the driver about the state of the robot and its components.
 *

## Main Controller Controls

Based on the type of drive as well as the program orientation of the robot, the joysticks on the main controller are used:


- **Left Joystick (Vertical Axis)**: Controls the forward and backward movement of the robot.
- **Right Joystick (Horizontal Axis)**: Controls the left and right movement (turning) of the robot.
---

- **R1 Button**: Activates the intake motor to push out objects.
- **L1 Button**: Activates the intake motor to pull in objects.

---
- **Digital Up Button**: Toggles the drivetrain orientation (forward or backward).
- **Digital Down Button**: Executes the autonomous routine during user control.
- **Digital Right Button**: Toggles the drivetrain reversal.
- **Digital Left Button**: Switches control between the main and partner controllers if the partner controller is connected.

---
- **Digital B Button**: Toggles the state of the MoGo mech between grabbing and not grabbing.
- **Digital Y Button**: This button toggles the state of the sweeper between active or retracted.
- ***NOT IMPLEMENTED -* Digital A Button**: This button controls whether the hang is active.
- **Digital X Button**: This button suspends the task that runs the lady brown warning system. On continuation of the task, the current location of the motor is considered as a 0 location.
---

- **R2 Button**: Pulls the Lady Brown down to its loading zone.
- **L2 Button**: Lifts the Lady Brown towards the neutral wall stake.


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
