#include "robot/auton.h"
#include "globals.h"
#include "pros/apix.h"

using namespace Robot;
using namespace Robot::Globals;

int Autonomous::auton = 4;


void Autonomous::Auton1() {
if(Autonomous::auton == 1){

}
}

void Autonomous::Auton2() {
	if(Autonomous::auton == 2){

	}
}


void Autonomous::Auton3() {
    // Autonomous routine for the Skills challenge

	for (int i=0; i < 30000; i++) {
		pros::delay(1);
	}
	drive_.move(100);
	pros::delay(1700);
	drive_.brake();
	drive_left.move(75);
	pros::delay(75);
	drive_.brake();
	drive_.move(100);
	pros::delay(2000);
	drive_.brake();

	// else {
	// 	for (int i=0; i < 30000; i++) {
	// 		punchers.move(105);
	// 		pros::delay(1);
	// 	}
	// }
	// //movement
	// if (pros::c::registry_get_plugged_type(15) == pros::c::E_DEVICE_IMU) {
	// 	chassis.setPose(-55.174, -55.383, 45);
	// 	chassis.follow("auton_skills_1.txt", 5000, 15);
	// 	chassis.follow("auton_skills_2.txt", 10000, 15);
	// }

}

void Autonomous::Auton4() {
 
}



// Takes in two parameters: The autonomous value as well as the puncher object.
void Autonomous::AutoDrive(bool autono = false) {
	// Keep the switcher running while the controller down button has not been pressed and the time period is not autonomous
	// Compare the current auton value to run the auton routine

    if(Autonomous::auton == 1){
        Auton1();
    }

    if(Autonomous::auton == 2){
        Auton2();
    }

    if(Autonomous::auton == 3){
        Auton3();
    }
	if(Autonomous::auton == 4){
        Auton4();
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
				autonName = "Skills Challenge";
			}
			if (auton == 4) {
				autonName = "";
			}
			// Set the controllet text to the current autonomous routine value
			pros::lcd::print(3, "Autonomous prog: %s", autonName);

	}
	
		
    
}