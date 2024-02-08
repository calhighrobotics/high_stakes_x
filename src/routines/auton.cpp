#include "robot/auton.h"
#include "globals.h"
#include "pros/apix.h"


namespace Autonomous {
	void Auton1() {
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

void Auton2() {
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


void Auton3() {
    
    // Autonomous routine for the Skills challenge
        while (true) {
            Puncher.move(95);
        }

}

}


void Autonomous::AutoDrive() {

    if(Autonomous::auton == 1){
        Auton1();
    }

    if(Autonomous::auton == 2){
        Auton2();
    }

    if(Autonomous::auton == 3){
        Auton3();
    }

}

void Autonomous::AutonSwitcher() {

    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
			if (Autonomous::auton == 1) {
				// intake
				AutoDrive();
			}
			if (Autonomous::auton == 2) {
				// Four Bar
				
				AutoDrive();
				
			}
			if (Autonomous::auton == 3) {
				// Flywheel
				AutoDrive();
			}

			Autonomous::auton = Autonomous::auton + 1;

			// Checks if the toggler goes out of bounds.
			if (Autonomous::auton == 3) {
				Autonomous::auton = 1;
			}

		}
    
    
}