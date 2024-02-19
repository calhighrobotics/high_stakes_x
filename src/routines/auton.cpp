#include "robot/auton.h"
#include "globals.h"
#include "pros/apix.h"

using namespace Robot;

int Autonomous::auton = 1;

void Autonomous::Auton1() {
if(Autonomous::auton == 1){
	// Autonomous for Far side defensive zone.
	
	if (pros::c::registry_get_plugged_type(13) == pros::c::E_DEVICE_IMU) {
		// 36.994 -58.128 0
		chassis.setPose(36.994, -58.128, 0);
		chassis.followPath("home_side_auton_path_1.txt");
		chassis.followPath("home_side_auton_path_2.txt");
		chassis.followPath("home_side_auton_path_3.txt");
		chassis.followPath("home_side_auton_path_4.txt");
		chassis.followPath("home_side_auton_path_5.txt");
	}
	else {
		drive_.move_velocity(150);
		pros::delay(5000);
		drive_.brake();
		drive_right.move_velocity(180);
		pros::delay(350);
		drive_.move_velocity(170);
		pros::delay(3000);
		
	}
}
}

void Autonomous::Auton2() {
	if(Autonomous::auton == 2){
		// Autonomous for near side offensive zone.

		if (pros::c::registry_get_plugged_type(13) == pros::c::E_DEVICE_IMU) {
			// -36.851 -58.638 0
			chassis.setPose(-36.851, -58.638, 0);
			chassis.followPath("far_side_auton_path_1.txt");
			chassis.followPath("far_side_auton_path_2.txt");
			chassis.followPath("far_side_auton_path_3.txt");
			chassis.followPath("far_side_auton_path_4.txt");
		}
		else {
			drive_.move_velocity(150);
			pros::delay(2000);
			drive_.brake();
			drive_right.move_velocity(180);
			pros::delay(550);
			drive_right.brake();
			drive_.move_velocity(170);
			pros::delay(3000);
		}
		
	}
}


void Autonomous::Auton3(Puncher &puncher) {
    
	puncher.setDistancePuncher(true);
    // Autonomous routine for the Skills challenge
        while (true) {
            puncher.run(Autonomous::auton);
        }

}

// Takes in two parameters: The autonomous value as well as the puncher object.
void Autonomous::AutoDrive(Puncher &puncher, bool autono = false) {

	// Keep the switcher running while the controller down button has not been pressed and the time period is not autonomous
	if (autono == false) {
		AutonSwitcher();
	}
	
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

		}
    
    
}