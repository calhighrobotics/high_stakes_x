#include "robot/auton.h"

#include "main.h"  // IWYU pragma: export
// Globals header imports used subtypes
#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;

Autonomous::Mode Autonomous::auton = BLUE_RIGHT;

ASSET(red_right_pt1_txt);
ASSET(red_right_pt2_txt);
ASSET(red_right_pt3_txt);
ASSET(red_right_pt4_txt);
ASSET(red_right_pt5_txt);

ASSET(red_left_pt1_txt);
ASSET(red_left_pt2_txt);
ASSET(red_left_pt3_txt);
ASSET(red_left_pt4_txt);
ASSET(red_left_pt5_txt);

// Red Left
void Autonomous::Auton1(Intake &intake, Latch &latch) {
	intake.async();

	chassis.setPose(-148.132, -58.408, 190);
	//robot backs up into wallstake and is ready to outake
	chassis.follow(red_right_pt1_txt, 15, 5000);

  intake.score();
  intake.toggle();
  // robot moves forward and intakes red ring on top of stack
  chassis.follow(red_right_pt2_txt, 15, 5000);

  // robot moves backward and stops at mobile goal. ready to latch and outake
  // ring
  chassis.follow(red_right_pt3_txt, 15, 5000);
  latch.toggle();
  intake.score();
  intake.toggle();

  // robot drags mobile goal and intakes bottom of ring of 2ring stack then
  // stops. ready to outake to mobile goal
  //  then unlatches mobile goal
  chassis.follow(red_right_pt4_txt, 15, 5000);
  intake.score();
  latch.toggle();

  // robot ends in contact with tower
  chassis.follow(red_right_pt5_txt, 15, 5000);
}

// Red Right
void Autonomous::Auton2(Intake &intake, Latch &latch) {
  chassis.setPose(-146.76, 63.046, 10);
  // robot backs up into wallstake and is ready to outake
  chassis.follow(red_left_pt1_txt, 15, 5000);
  intake.score();
  intake.toggle();

  // robot moves and intakes ring from top of 2ring stack.
  chassis.follow(red_left_pt2_txt, 15, 5000);
  intake.toggle();

  // robot moves backward toward mobile goal. Ready to latch then score.
  chassis.follow(red_left_pt3_txt, 15, 5000);
  latch.toggle();
  intake.score();

  // robot turns around and intakes ring from bottom of 2ring stack.
  chassis.follow(red_left_pt4_txt, 15, 5000);
  intake.score();
  latch.toggle();

  // robot ends in contact with mobile goal
  chassis.follow(red_left_pt5_txt, 15, 5000);
}

// Blue left
void Autonomous::Auton3(Intake &intake, Latch &latch) {}

/*
 * @todo Flesh out this method before the competition in order to make it a full
 * solo awp autonomous. Blue right
 */
void Autonomous::Auton4(Intake &intake, Latch &latch) {
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

  chassis.setPose(0, 0, 0);
  // move 48" forwards
  chassis.moveToPoint(0, 72, 3500, {.maxSpeed = 110}, true);
  chassis.turnToHeading(180, 1000, {.maxSpeed = 90}, false);

  chassis.setPose(0, 0, 0);
  chassis.moveToPoint(0, 24, 1000, {.maxSpeed = 110});
  chassis.turnToHeading(0, 1200, {.maxSpeed = 110}, false);
}

void Autonomous::Auton5(Intake &intake, Latch &latch) {
  // Autonomous routine for the Skills challenge
}

// Takes in two parameters: The autonomous value as well as the puncher object.
void Autonomous::AutoDrive(Intake &intake, Latch &latch) {
	// Keep the switcher running while the controller down button has not been pressed and the time period is not autonomous
	// Compare the current auton value to run the auton routine

    if(Autonomous::auton == RED_LEFT){
        Auton1(intake, latch);
    }

    if(Autonomous::auton == RED_RIGHT){
        Auton2(intake, latch);
    }

    if(Autonomous::auton == BLUE_LEFT){
        Auton3(intake, latch);
    }
	if(Autonomous::auton == BLUE_RIGHT){
        Auton4(intake, latch);
    }

	if(Autonomous::auton == SKILLS) {
		Auton5(intake, latch);
	}

}

// 
void Autonomous::AutonSwitcher() {


    if(autonToggleSwitch.get_new_press()) {
			pros::lcd::clear_line(3);
			
			if (auton == SKILLS) {
				autonName = "Red Leftˇ";
				auton = RED_LEFT;
			}
			else if (auton == RED_LEFT) {
				autonName = "Red Right";
				auton = RED_RIGHT;
			}
			else if (auton == RED_RIGHT) {
				autonName = "Blue Left";
				auton = BLUE_LEFT;
			}
			else if (auton == BLUE_LEFT) {
				autonName = "Blue Right";
				auton = BLUE_RIGHT;
			}
			else {
				autonName = "Skills Challenge";
				auton = SKILLS;
			}
			// Set the controllet text to the current autonomous routine value
			pros::lcd::print(3, "Autonomous prog: %s", autonName);

	}
	

    
}