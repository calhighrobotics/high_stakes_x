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

/* @brief variable is set in order to serve for the selector, which needs a static variable to keep track of the drive mode. It is synced back
* to the class variable in the run method.
*/
int Drivetrain::driveNum = 0;


// Run the drivetrain depending on the control mode
void Drivetrain::run() {

    if (Drivetrain::driveNum == 0) {
        Drivetrain::CurvatureDrive();
    }
    if (Drivetrain::driveNum == 1) {
        Drivetrain::ArcadeDrive();
    }
    if (Drivetrain::driveNum == 2) {
        Drivetrain::TankDrive();
    }
}

// Switch the drivetrain control mode between arcade and tank drive with the down button(between 1 and 2)
std::string Drivetrain::SwitchDrive() {

    Drivetrain::driveNum += 1;
    
    if (Drivetrain::driveNum == 3) {
        Drivetrain::driveNum = 0;
    }

    // Return the name of the drive mode
    if (Drivetrain::driveNum == 0) {
        std::cout << "Curvature Drive" << std::endl;
        return "Curvature Drive";
    }
    if (Drivetrain::driveNum == 1) {
        std::cout << "Arcade Drive" << std::endl;
        return "Arcade Drive";
    }
    if (Drivetrain::driveNum == 2) {
        std::cout << "Tank Drive" << std::endl;
        return "Tank Drive";
    }
    else {
        return "Error";
    }
}