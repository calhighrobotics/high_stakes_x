#include "globals.h"
#include "pros/abstract_motor.hpp"
#include "pros/motors.hpp"

/*
 * Although the following constants belong in their own seperate
 * files(auton.cpp, drivetriain.cpp), they are put here in order to maintain a
 * common location for all of the constants used by the program to belong in.
 * NOTE: This is the location where these variables are put into memory, but
 * they can be otherwise modified throughout the program.
 */

// Defines the objects that are used by the program for each of the individual
// subsystems.

namespace Robot {
namespace Globals {

pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Motor RightFront(6, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor LeftFront(-20, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor LeftBack(-10, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor RightBack(8, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor LeftMid(2, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor RightMid(-3, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor IntakeMotor(-9, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor HookMotor(4, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::adi::DigitalIn drivetrainToggleSwitch('G');
pros::adi::DigitalIn autonToggleSwitch('F');

pros::Optical colorSensor(4); // placeholder port number

pros::adi::Pneumatics LatchControl('A', false);
pros::adi::Pneumatics HangControl('B', true);

pros::Imu inertial_sensor(15);

pros::MotorGroup drive_left({LeftFront.get_port(), LeftMid.get_port(), LeftBack.get_port()});
pros::MotorGroup drive_right({RightFront.get_port(), RightMid.get_port(), RightBack.get_port()});
pros::MotorGroup drive_({LeftFront.get_port(), RightFront.get_port(), LeftMid.get_port(), RightMid.get_port(),
                         LeftBack.get_port(), RightBack.get_port()});

// Describes the lemlib objects that are used to control the autonomous
// functions of the robot.
lemlib::Drivetrain drivetrain{
    &drive_left,  // left drivetrain motors
    &drive_right, // right drivetrain motors
    12.25,       // track width
    lemlib::Omniwheel::OLD_325,
    450, // drivetrain rpm is 450
    2    // horizontal drift is 2
};

lemlib::OdomSensors sensors{
    nullptr,         // vertical tracking wheel 1
    nullptr,         // vertical tracking wheel 2
    nullptr,         // horizontal tracking wheel 1
    nullptr,         // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};

// forward/backward PID
// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors, &throttle_curve, &steer_curve);

} // namespace Globals

} // namespace Robot