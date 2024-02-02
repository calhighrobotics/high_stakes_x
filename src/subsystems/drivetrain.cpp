#include "main.h"
#include "api.h"

int Drivetrain::deadzone = 5;

static int CheckDeadzone(int ControllerInput) {
    if(std::abs(ControllerInput) < Drivetrain::deadzone) {
        return 0;
    return ControllerInput;
}
}

void Drivetrain::ArcadeDrive() {


    // Arcade Measurements
    int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    
    // std::abs takes the absolute value of whatever it is called on.
    // Thus, any values in range (-5,5) are discarded as 0.
    left = CheckDeadzone(left);
    right = CheckDeadzone(right);

    // Arcade movement
    // Move the left side of the robot
    drive_left.move(left + right);
    
    // Move the right side of the robot 
    drive_right.move(left - right);
}

void Drivetrain::TankDrive() {
    int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    // Arcade Measurements
    // int left = master.get_analog(pros::E_E_CONTROLLER_ANALOG_LEFT_Y);
    // int right = master.get_analog(pros::E_E_CONTROLLER_ANALOG_RIGHT_X);

    
    // std::abs takes the absolute value of whatever it is called on.
    // Thus, any values in range (-5,5) are discarded as 0.
    left = CheckDeadzone(left);
    right = CheckDeadzone(right);

    // Arcade movement
    // Move the left side of the robot
    drive_left.move(left);
    
    // Move the right side of the robot 
    drive_right.move(right);
}