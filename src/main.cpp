#include "main.h"
#include <ostream>

#include "api.h"
#include "pros/apix.h"
#include "pros/serial.h"


/*
  (      (     (      (     (   
  )\    (()    )\     )\   (_)  
 ((_)  ((_)   ((_)   ((_) (_))  
 (/ |  | __|  (/ |  (/ /  | |() 
  | |  |__ \   | |  / _ \ |  _ \
  |_|  |___/   |_|  \___/ |____/

*/


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */



void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(1, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void displayLocation() {
	while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // pri∟nt the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
        pros::delay(10);
    }
}

void displayHi() {
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


void initialize() {
	pros::lcd::initialize();
	
	if (pros::c::registry_get_plugged_type(13) == pros::c::E_DEVICE_IMU) {
		chassis.calibrate();

		chassis.setPose(0, 0, 90); // X: 0, Y: 0, Heading: 0
		// Setting an example start location for the robot so it is all relatativistic 
		pros::Task screenTask(displayLocation);
	}
	else {
		pros::Task screenTask(displayHi);
	}
	
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
	








/**
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
	
	Autonomous::AutonSwitcher();



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
        Drivetrain::ArcadeDrive();
		


		if (controller.get_digital(DIGITAL_L2)) {
			Puncher.move(127);
		}
		else if (controller.get_digital(DIGITAL_R2)) {
			Puncher.move(-127);
		}
		else {
			Puncher.brake();
		}


		if (controller.get_digital(DIGITAL_L1)) {
			Intake.move(127);
		}
		else if (controller.get_digital(DIGITAL_R1)) {
			Intake.move(-127);
		}
		else {
			Intake.brake();
		}

		// Catapult controller, uses the X button holded down to push the elevation up.
		

		// Intake controller, moves the left and right intakes and stops them if nothing is pressed.
	

		robotWings.check();

	


		
    


        pros::delay(2); // Small delay to reduce CPU usage
    }
	
	
}
