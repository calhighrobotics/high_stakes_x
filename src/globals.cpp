#include "globals.h"
#include "pros/abstract_motor.hpp"
#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/vision.h"
#include "pros/vision.hpp"

/*
 * Although the following constants belong in their own seperate
 * files(auton.cpp, drivetriain.cpp), they're put here in order to maintain a
 * common location for all of the constants used by the program to belong in.
 * NOTE: This is the location where these variables are put into memory, but
 * they can be otherwise modified throughout the program.
 */

// Defines the objects that are used by the program for each of the individual
// subsystems.

namespace Robot {
namespace Globals {

pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

pros::Motor RightFront(13, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor LeftFront(-19, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor LeftBack(-18, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor RightBack(12, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor LeftMid(20, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor RightMid(-11, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor IntakeMotor(-9, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor HookMotor(7, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor LadyBrownMotor(-3, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

pros::adi::Pneumatics LatchControl('A', false);
pros::adi::Pneumatics SweeperControl('B', false);

pros::Distance distance_sensor(10);
pros::Rotation lateral_sensor(16);
pros::Rotation horizontal_sensor(17);

pros::Rotation LadyBrownRotation(8);

pros::Imu inertial_sensor(2);

// Vision sensor configuration
pros::Optical colorSensor(4);

pros::vision_signature_s_t RED_SIG =
    pros::c::vision_signature_from_utility(1, -4653, -3619, -4136, 9831, 11725, 10778, 2.5, 0);

pros::vision_signature_s_t BLUE_SIG =
    pros::c::vision_signature_from_utility(2, 9187, 12161, 10674, -375, 1327, 476, 2.5, 0);
pros::vision_signature_s_t BLUE_DARK_SIG =
    pros::c::vision_signature_from_utility(3, -4793, -4173, -4483, 1069, 2765, 1917, 3, 0);

// Pros motor groups - most used by lemlib
pros::MotorGroup drive_left({LeftFront.get_port(), LeftMid.get_port(), LeftBack.get_port()});
pros::MotorGroup drive_right({RightFront.get_port(), RightMid.get_port(), RightBack.get_port()});
pros::MotorGroup drive_({LeftFront.get_port(), RightFront.get_port(), LeftMid.get_port(), RightMid.get_port(),
                         LeftBack.get_port(), RightBack.get_port()});

// Lemlib objects - Used by lemlib drive and odometry functions
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_sensor, 2, -2.75);
lemlib::TrackingWheel vertical_tracking_wheel(&lateral_sensor, 2, -1);

// Describes the lemlib objects that are used to control the autonomous
// functions of the robot.
lemlib::Drivetrain drivetrain{
    &drive_left,  // left drivetrain motors
    &drive_right, // right drivetrain motors
    12.25,        // track width
    lemlib::Omniwheel::OLD_325,
    450, // drivetrain rpm is 450
    2    // horizontal drift is 2
};

lemlib::OdomSensors sensors{
    &vertical_tracking_wheel,   // vertical tracking wheel 1
    nullptr,                    // vertical tracking wheel 2
    &horizontal_tracking_wheel, // horizontal tracking wheel 1
    nullptr,                    // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor            // inertial sensor
};

// forward/backward PID
// lateral PID controller
lemlib::ControllerSettings lateral_controller(6.5, // proportional gain (kP)
                                              0,   // integral gain (kI)
                                              35,  // derivative gain (kD)
                                              0,   // anti windup
                                              0.5, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3,   // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20   // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2.1, // proportional gain (kP)
                                              0,   // integral gain (kI)
                                              14,  // derivative gain (kD)
                                              0,   // anti windup
                                              0.5, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              2,   // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0    // maximum acceleration (slew)
);

lemlib::ExpoDriveCurve throttle_curve(3,    // joystick deadband out of 127
                                      50,   // minimum output where drivetrain will move out of 127
                                      1 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3,   // joystick deadband out of 127
                                   17,  // minimum output where drivetrain will move out of 127
                                   1 // expo curve gain
);

lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors, &throttle_curve, &steer_curve);

} // namespace Globals

} // namespace Robot
