#include "robot/auton.h"
#include "globals.h"
#include "robot/drivetrain.h"
#include "robot/utility.h"
#include "main.h"
#include "pros/apix.h"

using namespace Robot;
using namespace Robot::Globals;

int Autonomous::auton = 4;
std::string Autonomous::autonName = "Red Left";

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

//Red Right
void Autonomous::Auton1(Intake &intake, Latch &latch) {
	
	chassis.setPose(-148.132, -58.408, 190);
	//robot backs up into wallstake and is ready to outake
	chassis.follow(red_right_pt1_txt, 15, 5000);

	intake.score();
	intake.toggle();
	// robot moves forward and intakes red ring on top of stack
	chassis.follow(red_right_pt2_txt, 15, 5000);

	// robot moves backward and stops at mobile goal. ready to latch and outake ring
	chassis.follow(red_right_pt3_txt, 15, 5000);
	latch.toggle();
	intake.score();
	intake.toggle();

	//robot drags mobile goal and intakes bottom of ring of 2ring stack then stops. ready to outake to mobile goal
	// then unlatches mobile goal
	chassis.follow(red_right_pt4_txt, 15, 5000);
	intake.score();
	latch.toggle();

	// robot ends in contact with tower
	chassis.follow(red_right_pt5_txt, 15, 5000);

}

//Red Left
void Autonomous::Auton2(Intake &intake, Latch &latch) {

	chassis.setPose(-146.76, 63.046, 10);
	//robot backs up into wallstake and is ready to outake
	chassis.follow(red_left_pt1_txt, 15, 5000);
	intake.score();
	intake.toggle();

	//robot moves and intakes ring from top of 2ring stack.
	chassis.follow(red_left_pt2_txt, 15, 5000);
	intake.toggle();

	//robot moves backward toward mobile goal. Ready to latch then score.
	chassis.follow(red_left_pt3_txt, 15, 5000);
	latch.toggle();
	intake.score();

	//robot turns around and intakes ring from bottom of 2ring stack.
	chassis.follow(red_left_pt4_txt, 15, 5000);
	intake.score();
	latch.toggle();

	//robot ends in contact with mobile goal
	chassis.follow(red_left_pt5_txt, 15, 5000);
}

//Blue Right
void Autonomous::Auton3(Intake &intake, Latch &latch) {
    
}

/*
* @todo Flesh out this method before the competition in order to make it a full solo awp autonomous. 
* Blue left
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
	std::cout << Autonomous::auton << std::endl;

    if(Autonomous::auton == 1){
        Auton1(intake, latch);	
    }

    if(Autonomous::auton == 2){
        Auton2(intake, latch);
    }

    if(Autonomous::auton == 3){
        Auton3(intake, latch);
    }

	if(Autonomous::auton == 4){
        Auton4(intake, latch);
    }

	if(Autonomous::auton == 5) {
		Auton5(intake, latch);
	}

}

// 
void Autonomous::AutonSwitcher() {
			

	Autonomous::auton = auton + 1;

	// Checks if the toggler goes out of bounds.
	if (Autonomous::auton == 6) {
		Autonomous::auton = 1;
	}

	
	if (auton == 1) {
		Autonomous::autonName = "Red Left";
		std::cout << Autonomous::autonName << std::endl;
	}
	if (auton == 2) {
		Autonomous::autonName = "Red Right";
		std::cout << Autonomous::autonName << std::endl;
	}
	if (auton == 3) {
		Autonomous::autonName = "Blue Left";
		std::cout << Autonomous::autonName << std::endl;
	}
	if (auton == 4) {
		Autonomous::autonName = "Blue Right";
		std::cout << Autonomous::autonName << std::endl;
	}
	if (auton == 5) {
		Autonomous::autonName = "Skills";
		std::cout << Autonomous::autonName << std::endl;
	}
			// Set the controllet text to the current autonomous routine valu

    
}