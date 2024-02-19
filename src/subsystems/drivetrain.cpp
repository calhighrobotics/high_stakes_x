#include "robot/drivetrain.h"
#include "api.h"
#include "globals.h"

using namespace Robot;

Drivetrain::driveMode = 0

int Drivetrain::CheckDeadzone(int ControllerInput) {
    if(std::abs(ControllerInput) < Drivetrain::deadzone) {
        return 0;
    }
    else {
        return ControllerInput;
    }
}

void Drivetrain::ArcadeDrive() {

    Drivetrain::deadzone = 5;
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

    Drivetrain::deadzone = 5;

    int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    
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

// Run the drivetrain depending on the control mode
void Drivetrain::run() {
    if (Drivetrain::driveMode == 0) {
        Drivetrain::ArcadeDrive();
    }
    if (Drivetrain::driveMode == 1) {
        Drivetrain::TankDrive();
    }
}


// Switch the drivetrain control mode between arcade and tank drive with the down button(between 1 and 2)
void Drivetrain::SwitchDrive() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        Drivetrain::driveMode = Drivetrain::driveMode + 1;
        if (Drivetrain::driveMode == 2) {
            Drivetrain::driveMode = 0;
        }
        controller.set_text(0, 0, "Drive Mode: %d", Drivetrain::driveMode);
    }
}