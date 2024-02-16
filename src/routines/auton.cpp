#include "robot/auton.h"
#include "globals.h"
#include "pros/apix.h"

using namespace Robot;

int Autonomous::auton = 1;

void Autonomous::Auton1() {
if(Autonomous::auton == 1){
	// Autonomous for Far side defensive zone.
	
	if (pros::c::registry_get_plugged_type(13) == pros::c::E_DEVICE_IMU) {
		chassis.setPose(-32.862, -58.306, 90);
		chassis.moveTo(-0.979, -59.856, 8000);
		chassis.moveTo(37.281, -58.478, 8000);
		chassis.moveTo(47.449, -52.791, 5000);
		chassis.moveTo(54.859, -43.869, 5000);
		chassis.moveTo(59.168, -27.113, 5000);

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
			chassis.setPose(37.281, -58.306, 35);
			chassis.moveTo(47.449, -52.791, 5000);
			chassis.moveTo(54.859, -43.869, 5000);
			chassis.moveTo(59.168, -27.113, 5000);
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


void Autonomous::Auton3(&Puncher puncher) {
    
	puncher.setDistancePuncher(true);
    // Autonomous routine for the Skills challenge
        while (true) {
            puncher.run();
        }

}

// Takes in two parameters: The autonomous value as well as the puncher object.
void Autonomous::AutoDrive(bool autono = false, Puncher& puncher) {

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

void Autonomous::AutonSwitcher() {


    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
			
			

			Autonomous::auton = auton + 1;

			// Checks if the toggler goes out of bounds.
			if (Autonomous::auton == 4) {
				Autonomous::auton = 1;
			}

		}
    
    
}