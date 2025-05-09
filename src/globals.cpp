#include "globals.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/vision.h"

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

pros::Motor RightFront(16, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor LeftFront(-13, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor LeftBack(-11, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor RightBack(14, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor LeftMid(12, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor RightMid(-15, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor IntakeMotor(-4, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor HookMotor(3, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor LadyBrownMotor(-10, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

pros::adi::Pneumatics LatchControl('A', false);
pros::adi::Pneumatics SweeperControl('B', false);
pros::adi::Pneumatics IntakeLift('D', false);

pros::adi::DigitalIn HookSwitch('C');


pros::Distance distance_sensor(6);
pros::Rotation lateral_sensor(-19);
pros::Rotation horizontal_sensor(-20);

pros::Rotation LadyBrownRotation(9);
pros::Rotation HookRotation(2);


pros::Imu inertial_sensor(17);

// Vision sensor configuration
pros::Optical colorSensor(5);

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
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_sensor, 2, 0.25);
lemlib::TrackingWheel vertical_tracking_wheel(&lateral_sensor, 2, -0.625);

// Describes the lemlib objects that are used to control the autonomous
// functions of the robot.
lemlib::Drivetrain drivetrain{
    &drive_left,  // left drivetrain motors
    &drive_right, // right drivetrain motors
    10.8,        // track width
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
lemlib::ControllerSettings lateral_controller(6.4, // proportional gain (kP)
                                              0,   // integral gain (kI)
                                              35,  // derivative gain (kD)
                                              3,   // anti windup
                                              0.5, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              2,   // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              115   // maximum acceleration (slew)
);

// 0,   // anti windup
// 0.5, // small error range, in inches
// 100, // small error range timeout, in milliseconds
// 3,   // large error range, in inches
// 500, // large error range timeout, in milliseconds
// 20  

// angular PID controller 2.2 17 Last test: kp 13 kd 75, kp was just before full oscilation, kd was just before jittering
lemlib::ControllerSettings angular_controller(3.27, // proportional gain (kP)
                                              0,   // integral gain (kI)
                                              27.5,  // derivative gain (kD)
                                              3,   // anti windup
                                              2, // small error range, in degrees
                                              90, // small error range timeout, in milliseconds
                                              3,   // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0     // maximum acceleration (slew)
);

// 2, // small error range, in degrees
// 80, // small error range timeout, in milliseconds
// 3,   // large error range, in degrees
// 500, // large error range timeout, in milliseconds
// 0

lemlib::ExpoDriveCurve throttle_curve(1,    // joystick deadband out of 127
                                      35,   // minimum output where drivetrain will move out of 127
                                      1.002 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(1,   // joystick deadband out of 127
                                   16,  // minimum output where drivetrain will move out of 127
                                   1.0084 // expo curve gain
);

lemlib::ExpoDriveCurve arcade_turn_curve(1,   // joystick deadband out of 127
                                   8,  // minimum output where drivetrain will move out of 127
                                   1.016 // expo curve gain
);

lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors, &throttle_curve, &steer_curve);

} // namespace Globals

} // namespace Robot
