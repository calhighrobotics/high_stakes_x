#pragma once
#include "api.h"
#include "lemlib/api.hpp"

// The following files are imported in order to provide type definitions into the compiler that allows for the objecys to
#include "robot/wings.h"

namespace Robot {
extern pros::Controller controller;

extern Robot::Wings robotWings;

extern pros::Motor RightFront;
extern pros::Motor LeftFront;
extern pros::Motor LeftBack;
extern pros::Motor RightBack;
extern pros::Motor LeftMid;
extern pros::Motor PuncherMotor;
extern pros::Motor PuncherMotor2;
extern pros::Motor RightMid;
extern pros::Motor Intake;

extern pros::Imu inertial_sensor;
extern pros::Distance distance;


extern pros::ADIDigitalOut wing;
extern pros::ADIDigitalOut wing2;
extern pros::ADIDigitalOut pto_1;
extern pros::ADIDigitalOut pto_2;

extern pros::Motor_Group punchers;
extern pros::Motor_Group drive_left;
extern pros::Motor_Group drive_right;
extern pros::Motor_Group drive_;

extern lemlib::Drivetrain_t drivetrain;

extern lemlib::OdomSensors_t sensors;


// forward/backward PID
extern lemlib::ChassisController_t lateralController;
 
// turning PID
extern lemlib::ChassisController_t angularController;

extern lemlib::Chassis chassis;
} // namespace Robot