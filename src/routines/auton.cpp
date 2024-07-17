#include "robot/auton.h"
#include "globals.h"
#include "robot/drivetrain.h"
#include "robot/utility.h"
#include "main.h"
#include "pros/apix.h"

using namespace Robot;
using namespace Robot::Globals;

int Autonomous::auton = 4;

ASSET(path_right_4_winpoint_pt1_txt);
ASSET(path_right_4_winpoint_pt2_txt);
ASSET(path_right_4_winpoint_pt3_txt);
ASSET(path_right_4_winpoint_pt4_txt);
ASSET(path_right_4_winpoint_pt5_txt);

void Autonomous::Auton1(Intake &intake, Latch &latch) {
	chassis.setPose(-148.132, -58.408, 190);
	//robot backs up into wallstake and is ready to outake
	chassis.follow(path_right_4_winpoint_pt1.txt, 15, 5000);

	intake.score();

	// robot moves forward and is ready to intake red ring on top of 2ring stack
	chassis.follow(path_right_4_winpoint_pt2.txt, 15, 5000);
	intake.toggle();
	intake.interval(5000);

	// robot moves backward and stops at mobile goal. ready to latch and outake ring
	chassis.follow(path_right_4_winpoint_pt3.txt, 15, 5000);
	latch.toggle();
	intake.score();

	//robot drags mobile goal and stops. ready to intake bottom of ring of 2ring stack + outake to mobile goal
	// then unlatches mobile goal
	chassis.follow(path_right_4_winpoint_pt4.txt, 15, 5000);
	intake.toggle();
	intake.interval(5000);
	latch.toggle();
	intake.score();

	// robot ends in contact with tower
	chassis.follow(path_right_4_winpoint_pt5.txt, 15, 5000);

}

void Autonomous::Auton2(Intake &intake, Latch &latch) {

}


void Autonomous::Auton3(Intake &intake, Latch &latch) {
    // Autonomous routine for the Skills challenge
}

void Autonomous::Auton4(Intake &intake, Latch &latch) {
 
}



// Takes in two parameters: The autonomous value as well as the puncher object.
void Autonomous::AutoDrive(Intake &intake, Latch &latch) {
	// Keep the switcher running while the controller down button has not been pressed and the time period is not autonomous
	// Compare the current auton value to run the auton routine

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

}

// 
void Autonomous::AutonSwitcher() {


    if(autonToggleSwitch.get_new_press()) {
			pros::lcd::clear_line(3);
			

			Autonomous::auton = auton + 1;

			// Checks if the toggler goes out of bounds.
			if (Autonomous::auton == 5) {
				Autonomous::auton = 1;
			}

			
			if (auton == 1) {
				autonName = "";
			}
			if (auton == 2) {
				autonName = "";
			}
			if (auton == 3) {
				autonName = "";
			}
			if (auton == 4) {
				autonName = "Skills Challenge";
			}
			// Set the controllet text to the current autonomous routine value
			pros::lcd::print(3, "Autonomous prog: %s", autonName);

	}
	

    
}