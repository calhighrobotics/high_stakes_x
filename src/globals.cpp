#include "globals.h"
#include "api.h"
#include "robot/auton.h"
#include "robot/drivetrain.h"



/*
* Although the following constants belong in their own seperate files(auton.cpp, drivetriain.cpp), they are put here in order to maintain 
* a common location for all of the constants used by the program to belong in.
* NOTE: This is the location where these variables are put into memory, but they can be otherwise modified throughout the program.
*/

// Defines the objects that are used by the program for each of the individual subsystems.

namespace Robot {
    namespace Globals {

pros::Controller controller (pros::E_CONTROLLER_MASTER);
pros::Motor RightFront (6, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor LeftFront (-5, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor LeftBack (-7, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor RightBack (8, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor LeftMid (-2, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor RightMid (3, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor IntakeMotor (-9, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

pros::Imu inertial_sensor(15);
pros::Distance distance(18);

pros::adi::DigitalOut Elevator ('D');

pros::adi::DigitalIn puncherToggleSwitch('E');
pros::adi::DigitalIn autonToggleSwitch('F');
pros::adi::DigitalIn drivetrainToggleSwitch('G');

pros::MotorGroup drive_left({LeftFront.get_port(), LeftMid.get_port(), LeftBack.get_port()});
pros::MotorGroup drive_right({RightFront.get_port(), RightMid.get_port(), RightBack.get_port()});
pros::MotorGroup drive_({LeftFront.get_port(), RightFront.get_port(), LeftMid.get_port(), RightMid.get_port(), LeftBack.get_port(), RightBack.get_port()});


// Describes the lemlib objects that are used to control the autonomous functions of the robot. 
lemlib::Drivetrain drivetrain {
    &drive_left, // left drivetrain motors
    &drive_right, // right drivetrain motors
    10, // track width
    lemlib::Omniwheel::OLD_325,
    3.25, // wheel diameter - 3.25 on competition bot, 4 on test drivetrain
	450 // wheel rpm - 360 rpm for competition bot, 200 for test drivetrain
};



lemlib::OdomSensors sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};


// forward/backward PID
lemlib::ControllerSettings lateral_controller {
    33, // kP
    0, // kI
    300, // kD
    2, // Anti Windup
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    10 // slew rate
};
 
// turning PID
lemlib::ControllerSettings angular_controller {
    6, // kP
    0, // kI
    47, // kD
    2, // Anti Windup
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0.5 // slew rate
};

lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

lemlib::Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors,
                        &throttle_curve, 
                        &steer_curve
);

    }
}