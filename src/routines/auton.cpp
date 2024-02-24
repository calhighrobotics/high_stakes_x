#include "robot/auton.h"
#include "globals.h"
#include "pros/apix.h"

using namespace Robot;
using namespace Robot::Globals;

int Autonomous::auton = 1;


void Autonomous::Auton1() {
if(Autonomous::auton == 1){
	// Autonomous for Far side defensive zone.
	
	if (pros::c::registry_get_plugged_type(15) == pros::c::E_DEVICE_IMU) {
		// 36.994 -58.128 0
		chassis.setPose(36.994, -58.128, 0);
		chassis.follow("home_side_auton_path_1.txt", 2000, 15);
		chassis.follow("home_side_auton_path_2.txt", 2000, 15);
		chassis.follow("home_side_auton_path_3.txt", 2000, 15);
		chassis.follow("home_side_auton_path_4.txt", 2000, 15);
		chassis.follow("home_side_auton_path_5.txt", 2000, 15);
		chassis.follow("home_side_auton_path_6.txt", 2000, 15);
	}
	else {
		drive_.move(-100);
		pros::delay(1700);
		drive_left.move(100);
		pros::delay(100);
		drive_.move(-85);
		pros::delay(1000);
		drive_.brake();
		drive_.move(85);
		pros::delay(100);
		
		
	}
}
}

void Autonomous::Auton2() {
	if(Autonomous::auton == 2){
		// Autonomous for near side offensive zone.

		if (pros::c::registry_get_plugged_type(15) == pros::c::E_DEVICE_IMU) {
			// -36.851 -58.638 0
			chassis.setPose(-36.851, -58.638, 0);
			chassis.follow("far_side_auton_path_1.txt", 2000, 15);
			chassis.follow("far_side_auton_path_2.txt", 2000, 15);
			chassis.follow("far_side_auton_path_3.txt", 2000, 15);
			chassis.follow("far_side_auton_path_4.txt", 2000, 15);
		}
		else {
			drive_.move(-100);
			pros::delay(2000);
			drive_left.move(100);
			pros::delay(300);
			drive_.move(-85);
			pros::delay(600);
			drive_.brake();
			drive_.move(85);
			pros::delay(100);
		}
		
	}
}


void Autonomous::Auton3(Puncher &puncher) {
    // Autonomous routine for the Skills challenge
	if (pros::c::registry_get_plugged_type(18) == pros::c::E_DEVICE_DISTANCE) {
		for (int i=0; i < 30000; i++) {
			puncher.DistanceRun();
			pros::delay(1);
		}
	}
	else {
		for (int i=0; i < 30000; i++) {
			punchers.move(105);
			pros::delay(1);
		}
	}
	//movement
	if (pros::c::registry_get_plugged_type(15) == pros::c::E_DEVICE_IMU) {
		chassis.setPose(-55.174, -55.383, 45);
		chassis.follow("auton_skills_1.txt", 5000, 15);
		chassis.follow("auton_skills_2.txt", 10000, 15);
	}

}



// Takes in two parameters: The autonomous value as well as the puncher object.
void Autonomous::AutoDrive(Puncher &puncher, bool autono = false) {
	// Keep the switcher running while the controller down button has not been pressed and the time period is not autonomous
	// Compare the current auton value to run the auton routine
    if(Autonomous::auton == 1){
        Auton1();
    }

    if(Autonomous::auton == 2){
        Auton2();
    }

    if(Autonomous::auton == 3){
        Auton3(puncher);
    }

}
// 
void Autonomous::AutonSwitcher() {


    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
			
			

			Autonomous::auton = auton + 1;

			// Checks if the toggler goes out of bounds.
			if (Autonomous::auton == 4) {
				Autonomous::auton = 1;
			}
			
			
			// Set the controllet text to the current autonomous routine value
			controller.print(0, 0, "Autonomous prog: %d", Autonomous::auton);

	}
	
		
    
}