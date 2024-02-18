#include "globals.h"
#include "api.h"
#include "robot/auton.h"
#include "robot/drivetrain.h"
#include "robot/wings.h"



/*
* Although the following constants belong in their own seperate files(auton.cpp, drivetriain.cpp), they are put here in order to maintain 
* a common location for all of the constants used by the program to belong in.
* NOTE: This is the location where these variables are put into memory, but they can be otherwise modified throughout the program.
*/

// Defines the objects that are used by the program for each of the individual subsystems.

namespace Robot {

pros::Controller controller (pros::E_CONTROLLER_MASTER);
pros::Motor RightFront (6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor LeftFront (-5, pros:: E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor LeftBack (-7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor RightBack (8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor LeftMid (-2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor PuncherMotor (19, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor PuncherMotor2 (-20, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor RightMid (3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor IntakeMotor (-9, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Imu inertial_sensor(15);
pros::Distance distance(18);
pros::ADIDigitalOut wing ('A');
pros::ADIDigitalOut wing2 ('D');
pros::ADIDigitalOut pto_1 ('B');
pros::ADIDigitalOut pto_2 ('C');

pros::Motor_Group punchers ({PuncherMotor, PuncherMotor2});
pros::Motor_Group drive_left ({LeftFront, LeftMid, LeftBack});
pros::Motor_Group drive_right ({RightFront, RightMid, RightBack});
pros::Motor_Group drive_ ({LeftFront, RightFront, LeftMid, RightMid, LeftBack, RightBack});


// Describes the lemlib objects that are used to control the autonomous functions of the robot. 
lemlib::Drivetrain_t drivetrain {
    &drive_left, // left drivetrain motors
    &drive_right, // right drivetrain motors
    11.75, // track width
    3.25, // wheel diameter - 3.25 on competition bot, 4 on test drivetrain
	360 // wheel rpm - 360 rpm for competition bot, 200 for test drivetrain
};

lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};


// forward/backward PID
lemlib::ChassisController_t lateralController {
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);

}