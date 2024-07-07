#include "main.h"
#include <ostream>

#include "api.h"
#include "pros/apix.h"
#include "pros/serial.h"

using namespace Robot;
using namespace Robot::Globals;
/*
  (      (     (      (     (   
  )\    (()    )\     )\   (_)  
 ((_)  ((_)   ((_)   ((_) (_))  
 (/ |  | __|  (/ |  (/ /  | |() 
  | |  |__ \   | |  / _ \ |  _ \
  |_|  |___/   |_|  \___/ |____/

*/


/**
 * @file main.cpp
 * @brief This file contains the main code for the robot's operation.
 */


namespace Robot {
/**
 * @brief Structure that holds instances of all robot subsystems.
 */
struct RobotSubsystems {
	Robot::Autonomous autonomous;
	Robot::Drivetrain drivetrain;
	Robot::Intake intake;
} subsystem;
}

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */



void toggles() {
	while (true)
	{
        subsystem.autonomous.AutonSwitcher();
		subsystem.drivetrain.SwitchDrive();
		
		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			pros::lcd::print(4, "toggler stopped");
			break;
		}

		// Exits the loop if the up button is pressed

		pros::delay(30);
	}
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


void initialize() {

	pros::lcd::initialize();

	// if (pros::c::registry_get_plugged_type(15) == pros::c::E_DEVICE_IMU) {
	chassis.calibrate();  
	chassis.setPose(0, 0, 0);
	
	
	pros::Task screenTask(Robot::Utility::display);
	
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */



void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.<asd></asd>
 */
void competition_initialize() {
	// Allows the user to select the autonomous routine, drive control type as well as whether the distance puncher is enabled.
	// The user can select the auton routine by pressing the right buttons on the controller.
	// The user can select the drive control type by pressing the down button on the controller.
	// The user can select the distance puncher by pressing the left button on the controller.
	// The state of each subsystem is displayed on the controller screen.

	toggles();
	
}






/**6
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	
	
	subsystem.autonomous.AutoDrive(true);



}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	
    while (true) {

		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			competition_initialize();
		}
		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			autonomous();
		}

        subsystem.drivetrain.run();
		


		

		// Catapult controller, uses the X button holded down to push the elevation up.
		subsystem.intake.run();

		// Intake controller, moves the left and right intakes and stops them if nothing is pressed.
	


        pros::delay(10); // Small delay to reduce CPU usage
    }
	
	
}