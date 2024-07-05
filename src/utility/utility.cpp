#include "robot/utility.h"
#include "api.h"
#include "pros/apix.h"
#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;
/**
 * \todo Figure out a way to send an event to the different objects to toggle between the different subsystems.
*/
void Utility::toggleSubsystemOptions(Autonomous &auton, Drivetrain &drive, Puncher &punch) {
    // Allows the user to select the autonomous routine, drive control type as well as whether the distance puncher is enabled.
	// The user can select the auton routine by pressing the right buttons on the controller.
	// The user can select the drive control type by pressing the down button on the controller.
	// The user can select the distance puncher by pressing the left button on the controller.
	// The state of each subsystem is displayed on the controller screen.
	while (true)
	{
		punch.PuncherSwitch();
        auton.AutonSwitcher();
		drive.SwitchDrive();
		

		// Exits the loop if the up button is pressed

		pros::delay(50);
	}
}

void Utility::displayMotorVel() {
    // std::vector<std::int32_t> currents = drive_.get_current_draws();// get the current position of the robot
    pros::lcd::print(0, "Motor velocity draw");
    pros::lcd::print(1, "motor 2 vel: %lf", LeftFront.get_actual_velocity());
    pros::lcd::print(2, "motor 2 vel: %lf", RightFront.get_actual_velocity());
    pros::lcd::print(3, "motor 3 vel: %lf", LeftMid.get_actual_velocity());
    pros::lcd::print(4, "motor 4 vel: %lf", RightMid.get_actual_velocity());
    pros::lcd::print(5, "motor 5 vel: %lf", LeftBack.get_actual_velocity());
    pros::lcd::print(6, "motor 6 vel: %lf", RightBack.get_actual_velocity()); // print the x position// print the heading
    
}

void Utility::displayLocation() {
    using namespace Robot::Globals;

    lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
    pros::lcd::print(0, "x: %f", pose.x); // print the x position
    pros::lcd::print(1, "y: %f", pose.y); // pri∟nt the y position
    pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
}

void Utility::display() {
    while (true) {
        if (!pros::competition::is_disabled()) {
            // if (pros::c::registry_get_plugged_type(15) == 6) {
            Utility::displayLocation();
            // } 
            // else {
            //     Utility::displayMotorVel();
            // }
        }
        else {
            ;
        }
        pros::delay(10);
	}
}

