# 1516X - High Stakes

This is the [High Stakes repository](https://github.com/calhighrobotics/high_stakes_x) for team **1516X**

We are a VEX VRC team based in the Bay Area, California.

We have both a wiki that covers high-level programming, engineering, design, and team management topics, as well as Doxygen documentation for our codebase.

- [Wiki](https://calhighrobotics.github.io/1516x)
- [Doxygen Documentation](https://calhighrobotics.github.io/high_stakes_x)

We aim to have a cohesive codebase that covers many subsystems but also follows best practices in the C++ development space as well as bringing in new features through modularity.

## Features

We want to lead the space in feature availability. Therefore, we have taken inspiration from other teams as well as from our own issues that would be benificial to have a solution for.

- Controller-based:
   - Drivetrain Mode Switching (Curvature{cheesy} Drive, Arcade Drive, Tank Drive)
      - Controller curves - provided by Lemlib
   - Autonomous execution in user control
   - Drivetrain orientation toggling (ex: driving the backside of the robot forward)
   - Dual Controller:
      - Rumble-based notifications from partner to main controller
      - Main Controller switching using dual controller
- Sensor-based
   - Vision/Optical sensor-based ring skipping - based on color
- Autonomous
   - Lemlib-based odometry with 1 horizontal and 1 lateral wheel
   - PID-based autonomous movement
   - WIP - AWP autonomous routines for 6-motor 8 wheel drivetrain
- Pneumatic control for MoGo mech and passive hang
- QOL features:
   - Brain Screen:
      - Autonomous selector - uses LVGL
      - Odometry information + rotation sensor status in auton period
      - WIP - Driver control information screen using LVGL
- Codebase:
   - Meticulous branching/merging system with github
   - Object-oriented approach to codebase system representations
   - Modularization of subsystems/contstructs into classes


## File Organization

Having multiple programmers, we emphasize modularity in the codebase. That being said, the codebase is split up into:

```text
/include - Contains information about the declarations of various methods and how they would be used
   /screen - LVGL-related classes that are created by 1516X programs for GUI
   /electronic - Miscellaneous electronics-controlling classes
   /robot - Contains the header files and information custom for the actual robot.
/src - Contains implementation of the above methods and the definition, specific to the 1516X robot
/docs - Contains Robot/Driver specific documentation that would not fit best in the public wiki or the Doxygen page.
```

## Other Libraries

We use the following libraries to make our codebase possible. We are indebted to their contributioins to make this codebase possible. Check out their code for types and functions that we use as well.

- [PROS](https://pros.cs.purdue.edu/v5/pros-4/)
- [LemLib](https://lemlib.readthedocs.io/)
- [LVGL](https://docs.lvgl.io/8.3/)

## License

See [LICENSE](https://github.com/calhighrobotics/high_stakes_x/blob/main/LICENSE) for more information.
