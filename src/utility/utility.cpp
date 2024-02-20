#include "robot/utility.h"
#include "api.h"
#include "globals.h"

using namespace Robot;
// Takes in the Autonomous object, drivetrain object and puncher object  and sets the corresponding variables to the input values.
void Utility::toggleSubsystemOptions(Autonomous &auton, Drivetrain &drive, Puncher &punch) {
    // Allows the user to select the autonomous routine, drive control type as well as whether the distance puncher is enabled.
	// The user can select the auton routine by pressing the right buttons on the controller.
	// The user can select the drive control type by pressing the down button on the controller.
	// The user can select the distance puncher by pressing the left button on the controller.
	// The state of each subsystem is displayed on the controller screen.
	while (true)
	{
		auton.AutonSwitcher();
		drive.SwitchDrive();
		punch.PuncherSwitch();

		// Exits the loop if the up button is pressed

		pros::delay(10);
	}
}

void Utility::displayMotorVel() {
    while (true) {
	// std::vector<std::int32_t> currents = drive_.get_current_draws();// get the current position of the robot
        pros::lcd::print(0, "Motor velocity draw");
        pros::lcd::print(1, "motor 1 vel: %lf", LeftFront.get_actual_velocity());
        pros::lcd::print(2, "motor 2 vel: %lf", RightFront.get_actual_velocity());
        pros::lcd::print(3, "motor 3 vel: %lf", LeftMid.get_actual_velocity());
        pros::lcd::print(4, "motor 4 vel: %lf", RightMid.get_actual_velocity());
        pros::lcd::print(5, "motor 5 vel: %lf", LeftBack.get_actual_velocity());
        pros::lcd::print(6, "motor 6 vel: %lf", RightBack.get_actual_velocity()); // print the x position// print the heading
        pros::delay(10);
    }
}

void Utility::displayLocation() {
    while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // pri∟nt the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
        pros::delay(10);
    }
}