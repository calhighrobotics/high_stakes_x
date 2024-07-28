#include "robot/drivetrain.h"
#include "api.h"
#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;



int Drivetrain::CheckDeadzone(int ControllerInput) {
    if(std::abs(ControllerInput) < Drivetrain::deadzone) {
        return 0;
    }
    else {
        return ControllerInput;
    }
}

void Drivetrain::CurvatureDrive() {
    Drivetrain::deadzone = 5;

    int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    
    left = CheckDeadzone(left);
    right = CheckDeadzone(right);

    chassis.curvature(left, right);
}

void Drivetrain::ArcadeDrive() {

    Drivetrain::deadzone = 5;
    // Arcade Measurements
    int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    
    // std::abs takes the absolute value of whatever it is called on.
    // Thus, any values in range (-5,5) are discarded as 0.
    chassis.arcade(left, right, false, 0.6);

    pros::delay(15);
}

Drivetrain::Drivetrain() {
    Drivetrain::driveMode = CURVATURE_DRIVE;
}

void Drivetrain::TankDrive() {

    Drivetrain::deadzone = 5;

    int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    
    // std::abs takes the absolute value of whatever it is called on.
    // Thus, any values in range (-5,5) are discarded as 0.
    chassis.tank(left, right);

    pros::delay(15);
}

void Drivetrain::CurveDrive() {

    Drivetrain::deadzone = 5;

    int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    
    // std::abs takes the absolute value of whatever it is called on.
    // Thus, any values in range (-5,5) are discarded as 0.
    chassis.curvature(left, right);

    pros::delay(15);
}

// Set the deadzone for the drivetrain


// Run the drivetrain depending on the control mode
void Drivetrain::run() {
    if (Drivetrain::driveMode == CURVATURE_DRIVE) {
        Drivetrain::CurvatureDrive();
    }
    if (Drivetrain::driveMode == ARCADE_DRIVE) {
        Drivetrain::ArcadeDrive();
    }
    if (Drivetrain::driveMode == TANK_DRIVE) {
        Drivetrain::TankDrive();
    }
}


// Switch the drivetrain control mode between arcade and tank drive with the down button(between 1 and 2)
void Drivetrain::SwitchDrive() {
    if(drivetrainToggleSwitch.get_new_press()) {
        pros::lcd::clear_line(2);
        
        if (Drivetrain::driveMode == TANK_DRIVE) {
            Drivetrain::driveMode = CURVATURE_DRIVE;
            pros::lcd::set_text(2, "Drive: Curvature");
        }
        if (Drivetrain::driveMode == CURVATURE_DRIVE) {
            Drivetrain::driveMode = ARCADE_DRIVE;
            pros::lcd::set_text(2, "Drive: Arcade");
        }
        if (Drivetrain::driveMode == ARCADE_DRIVE) {
            Drivetrain::driveMode = TANK_DRIVE;
            pros::lcd::set_text(2, "Drive: Tank");
        }
    }
}