#include "main.h"

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
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
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
 * starts.
 */
void competition_initialize() {}

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
	pros::Controller controller (pros::E_CONTROLLER_MASTER);
  	pros::Controller controller2 (pros::E_CONTROLLER_PARTNER);
	pros::Motor RightFront (6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor LeftFront (-5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor LeftBack (-7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor RightBack (8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor LeftMid (-2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor Lift (10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor RightMid (3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor Lift2 (-9, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::ADIDigitalOut wing ('A');
	pros::ADIDigitalOut pto_1 ('B');
	pros::ADIDigitalOut pto_2 ('C');


	pros::Motor_Group drive_left ({LeftFront, LeftMid, LeftBack});
	pros::Motor_Group drive_right ({RightFront, RightMid, RightBack});
	pros::Motor_Group lift_motors ({Lift, Lift2});

	int system = 1;
	bool wings = false;

    while (true) {
        // Read joystick values

		// TANK DRIVE
		drive_left.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
		drive_right.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));


		// Using Arcade drive
		// int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        // int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        
        // // Move the left side of the robot
        // drive_left.move(leftY + rightX);
        
        // // Move the right side of the robot 
        // drive_right.move(leftY - rightX);

		if (controller.get_digital(DIGITAL_R1)) {
			lift_motors.move(127);
		}
		else if (controller.get_digital(DIGITAL_R2)) {
			lift_motors.move(-127);
		}
		else {
			lift_motors.brake();
		}

		// Catapult controller, uses the X button holded down to push the elevation up.
		

		// Intake controller, moves the left and right intakes and stops them if nothing is pressed.
	

		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
			wings = !wings;
		}

		if (wings) {
			wing.set_value(true);
		}
		else {
			wing.set_value(true);
		}

		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
			if (system == 1) {
				// intake
				controller.clear_line(0);
				pto_1.set_value(false);
				controller.print(1, 0, "System %d : Intake", system);
			}
			if (system == 2) {
				// Four Bar
				controller.clear_line(0);
				pto_1.set_value(true);
				pto_2.set_value(true);
				controller.print(1, 0, "System %d : 4-bar", system);
			}
			if (system == 3) {
				// Flywheel
				controller.clear_line(0);
				pto_1.set_value(true);
				pto_2.set_value(false);
				controller.print(1, 0, "System %d : Flywheel", system);
			}

			system = system + 1;

			// Checks if the toggler goes out of bounds.
			if (system == 4) {
				system = 1;
			}

		}


		
    


        pros::delay(2); // Small delay to reduce CPU usage
    }
	
	
}
