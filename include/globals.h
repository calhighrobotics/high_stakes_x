#pragma once
#include "api.h"
#include "lemlib/api.hpp"

extern bool wings;

extern pros::Controller controller;


extern pros::Motor RightFront;
extern pros::Motor LeftFront;
extern pros::Motor LeftBack;
extern pros::Motor RightBack;
extern pros::Motor LeftMid;
extern pros::Motor Puncher;
extern pros::Motor RightMid;
extern pros::Motor Intake;

extern pros::Imu inertial_sensor;


extern pros::ADIDigitalOut wing;
extern pros::ADIDigitalOut wing2;
extern pros::ADIDigitalOut pto_1;
extern pros::ADIDigitalOut pto_2;


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
