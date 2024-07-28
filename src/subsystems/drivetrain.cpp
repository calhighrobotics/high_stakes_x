#include "robot/drivetrain.h"

#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;

void Drivetrain::CurvatureDrive() {
  int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

  chassis.curvature(left, right);

  pros::delay(15);
}

void Drivetrain::ArcadeDrive() {
  // Arcade Measurements
  int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

  chassis.arcade(left, right, false, 0.6);

  pros::delay(15);
}

Drivetrain::Drivetrain() {
    Drivetrain::driveMode = CURVATURE_DRIVE;
}

void Drivetrain::TankDrive() {
  int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  chassis.tank(left, right);

  pros::delay(15);
}

/* @brief variable is set in order to serve for the selector, which needs a
 * static variable to keep track of the drive mode. It is synced back to the
 * class variable in the run method.
 */
int Drivetrain::driveNum = 0;

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

std::string Drivetrain::toggleDrive() {
  Drivetrain::driveNum += 1;
  if (Drivetrain::driveNum > 2) {
    Drivetrain::driveNum = 0;
  }
  return SwitchDrive(Drivetrain::driveNum);
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
// Switch the drivetrain control mode between arcade and tank drive with the
// down button(between 1 and 2)
std::string Drivetrain::SwitchDrive(int drive) {
  Drivetrain::driveNum = drive;

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
  } else {
    return "Error";
  }
}