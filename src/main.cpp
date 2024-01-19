#include "main.h"
#include "lemlib/api.hpp"


/*
           ___
          |_|_|
          |_|_|              _____
          |_|_|     ____    |*_*_*|
 _______   _\__\___/ __ \____|_|_   _______
/ ____  |=|      \  <_+>  /      |=|  ____ \
~|    |\|=|======\\______//======|=|/|    |~
 |_   |    \      |      |      /    |    |
  \==-|     \     |1516B |     /     |----|~~/
  |   |      |    |      |    |      |____/~/
  |   |       \____\____/____/      /    / /
  |   |         {----------}       /____/ /
  |___|        /~~~~~~~~~~~~\     |_/~|_|/
   \_/        |/~~~~~||~~~~~\|     /__|\
   | |         |    ||||    |     (/|| \)
   | |        /     |  |     \       \\
   |_|        |     |  |     |
              |_____|  |_____|
              (_____)  (_____)
              |     |  |     |
              |     |  |     |
              |/~~~\|  |/~~~\|
              /|___|\  /|___|\
             <_______><_______>
*/

typedef struct {
	float current;
	float kP;
	float kI;
	float kD;
	float target;
	float error;
	float integral;
	float derivative;
	float lastError;
	int   lastTime;
} pid;

pid PID;

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
// pros::Imu inertial_sensor(13);
pros::ADIDigitalOut wing ('A');
pros::ADIDigitalOut wing2 ('D');
pros::ADIDigitalOut pto_1 ('B');
pros::ADIDigitalOut pto_2 ('C');


pros::Motor_Group drive_left ({LeftFront, LeftMid, LeftBack});
pros::Motor_Group drive_right ({RightFront, RightMid, RightBack});
pros::Motor_Group lift_motors ({Lift, Lift2});

lemlib::Drivetrain_t drivetrain {
    &drive_left, // left drivetrain motors
    &drive_right, // right drivetrain motors
    11.75, // track width
    4, // wheel diameter - 3.25 on competition bot, 4 on test drivetrain
	200 // wheel rpm - 360 rpm for competition bot, 200 for test drivetrain
};

lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};


// forward/backward PID
lemlib::ChassisController_t lateralController {
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */


int subsystem = 1;
int auton = 1;
bool wings = false;
int deadzone = 5;

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

void initialize() {
	pros::lcd::initialize();
	chassis.calibrate();

	chassis.setPose(0, 0, 0); // X: 0, Y: 0, Heading: 0
     // Setting an example start location for the robot so it is all relatativistic 
	pros::Task screenTask(displayLocation);
	
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
void competition_initialize() {


}
	









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
	
	if(auton == 1){ 
		
		
		chassis.turnTo(36.285, -45.745, 2000);
		chassis.moveTo(25.987, 58.854, 200);
		chassis.moveTo(12.019, 96.538, 200);



		//run auton for Front Red 
	}
	if(auton == 2){ 
		
		chassis.moveTo(0, 0, 5000);
		chassis.moveTo(-18.131, 20.89, 5000);
		chassis.moveTo(-20.693, 64.444, 5000);
		chassis.moveTo(8.868, 98.34, 5000);


		//run auton for Front Red 
	}


	






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
        // Read joystick values

		// TANK DRIVE

        int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        
        // std::abs takes the absolute value of whatever it is called on.
        // Thus, any values in range (-5,5) are discarded as 0.
        if(std::abs(left) < deadzone) {
            left = 0;
        }
        if(std::abs(right) < deadzone) {
            right = 0;
        }
        
        // Drive the left side of the robot forward at joystick left Y speed
        drive_left.move(left);
        
        // Drive the right side of the robot forward at joystick right Y speed
        drive_right.move(right);
		// Using Arcade drive

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
			wing2.set_value(false);
		}
		else {
			wing.set_value(false);
			wing2.set_value(true);
		}

		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
			if (subsystem == 1) {
				// intake
				controller.clear_line(0);
				pto_1.set_value(false);
				controller.print(1, 0, "System %d : Intake", system);
			}
			if (subsystem == 2) {
				// Four Bar
				controller.clear_line(0);
				pto_1.set_value(true);
				pto_2.set_value(true);
				controller.print(1, 0, "System %d : 4-bar", system);
			}
			if (subsystem == 3) {
				// Flywheel
				controller.clear_line(0);
				pto_1.set_value(true);
				pto_2.set_value(false);
				controller.print(1, 0, "System %d : Flywheel", system);
			}

			subsystem = subsystem + 1;

			// Checks if the toggler goes out of bounds.
			if (subsystem == 4) {
				subsystem = 1;
			}

		}


		
    


        pros::delay(2); // Small delay to reduce CPU usage
    }
	
	
}
