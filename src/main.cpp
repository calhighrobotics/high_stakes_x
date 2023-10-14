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

void initRerun(int rf, int rb, int lf, int lb, /*int lm, int rm,*/ int cat, int intake) {
      uint8_t arr[6];
      arr[0] = rf;
      arr[1] = rb;
      arr[2] = lf;
      arr[3] = lb;
      //arr[4] = lm;
      //arr[5] = rm;
      arr[4] = cat;
      arr[5] = intake;
      //Brain.SDcard.savefile("rerun.txt", arr, sizeof(arr));
}

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
void autonomous() {}

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
	pros::Motor RightFront (2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor LeftFront (1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor LeftBack (3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor RightBack (4, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor LeftMid (10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor Elevation (20, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor RightMid (9, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor Catapult (7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor IntakeLeft (8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor IntakeRight (11, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::ADIDigitalOut piston1 ('A');

    while (true) {
        // Read joystick values
		int power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

		int left = power + turn;
		int right = power - turn;

		
		// EXPERIMENTAL DRIVETRAIN CODE - Not Working currently.
		RightFront.move(right);
		RightMid.move(right);
		RightBack.move(right);

		LeftFront.move(left);
		LeftMid.move(left);
		LeftBack.move(left);
		
		// Controls Catapult movement - uses A button to cock the catapult back, the Y button to release tension.
		if (controller.get_digital(DIGITAL_A)) {
			Catapult.move(127);
		}
		else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
			Catapult.move(-127);
		}
		else {
			Catapult.brake();
		}

		// Catapult controller, uses the X button holded down to push the elevation up.
		if (controller.get_digital(DIGITAL_X)) {
			Elevation.move(127);
		}
		else {
			Elevation.brake();
		}

		// Intake controller, moves the left and right intakes and stops them if nothing is pressed.
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			IntakeRight.move(127);
			IntakeLeft.move(127);
		}
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      IntakeRight.move(-127);
			IntakeLeft.move(-127);
    }
		else {
			IntakeRight.brake();
			IntakeLeft.brake();
		}

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      piston1.set_value(true);

    }


		
    


        pros::delay(2); // Small delay to reduce CPU usage
    }
	
	
}
