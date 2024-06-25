#include "robot/auton.h"
#include "globals.h"
#include "pros/apix.h"

using namespace Robot;
using namespace Robot::Globals;

int Autonomous::auton = 4;


void Autonomous::Auton1() {
if(Autonomous::auton == 1){
	// Autonomous for Far side defensive zone.
	int imuOn = 0;
	if (imuOn == 1) {
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
		drive_.move(-127);
		pros::delay(1900);
		// drive_left.move(100);
		// pros::delay(200);
		drive_.brake();
		drive_.move(65);
		pros::delay(500);
		drive_.brake();
		drive_.move(-127);
		pros::delay(1000);
		drive_.brake();
		drive_.move(65);
		pros::delay(200);
		drive_.brake();
		
		
	}
}
}

void Autonomous::Auton2() {
	if(Autonomous::auton == 2){
		// Autonomous for near side offensive zone.
		int imuOn = 1;
		if (imuOn == 1) {
			// -36.851 -58.638 0
			chassis.setPose(-36.851, -58.638, 0);
			chassis.follow("far_side_auton_path_1.txt", 2000, 15);
			chassis.follow("far_side_auton_path_2.txt", 2000, 15);
			chassis.follow("far_side_auton_path_3.txt", 2000, 15);
			chassis.follow("far_side_auton_path_4.txt", 2000, 15);
		}
		else {
			drive_.move(-100);
			pros::delay(1700);
			drive_right.move(100);
			pros::delay(200);
			drive_.brake();
			drive_.move(-85);
			pros::delay(600);
			drive_.brake();
			drive_.move(85);
			pros::delay(150);
			drive_.brake();
		}
		
	}
}


void Autonomous::Auton3(Puncher &puncher) {
    // Autonomous routine for the Skills challenge

	for (int i=0; i < 30000; i++) {
		puncher.DistanceRun();
		pros::delay(1);
	}
	FrontWing.set_value(true);
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
    // Autonomous routine for the Skills challenge
	// lemlib::Pose pose = chassis.getPose();
	// chassis.moveTo(0, 4, 2000);
	// IntakeMotor.move(88);
	// pros::delay(1400);
	// chassis.setPose(0, 0, 180);
	// chassis.moveTo(0, 37, 4000,65);
	// chassis.setPose(0, 0, 180);
	// chassis.turnTo(-22, 15, 2000);
	// chassis.setPose(0, 0, 0);
	// FrontWing.set_value(true);
	// chassis.moveTo(-20, 20, 2000, 120);
	// chassis.setPose(0, 0, 0);
	// chassis.turnTo(-25, -29, 2000, 70);
	// chassis.setPose(0, 0, 0);
	// IntakeMotor.move(-127);
	// chassis.moveTo(0, 10, 4000);
	// IntakeMotor.brake();
	// drive_.move(-70);
	// pros::delay(350);
	// drive_.brake();

	lemlib::Pose pose = chassis.getPose();
	chassis.moveTo(0, 4, 2000);
	IntakeMotor.move(88);
	pros::delay(600);
	chassis.setPose(0, 0, 180);
	chassis.moveTo(0, 37, 4000, 65);
	chassis.setPose(0, 0, 180);
	chassis.turnTo(22, -15, 2000);
	chassis.setPose(0, 0, 180);
	BackWing1.set_value(true);
	BackWing2.set_value(true);
	chassis.moveTo(-20, 20, 2000, 120);
	chassis.setPose(0, 0, 180);
	chassis.turnTo(-25, -29, 2000, 70);
	chassis.setPose(0, 0, 180);
	// IntakeMotor.move(-127);
	chassis.moveTo(0, 10, 4000);
	pros::delay(1000);
	BackWing1.set_value(false);
	BackWing2.set_value(false);
	drive_.move(80);
	pros::delay(500);
	drive_.brake();
	chassis.setPose(0, 0, 180);
	chassis.turnTo(-6, 40, 2000, 70);
	chassis.setPose(0, 0, 0);
	IntakeMotor.move(-127);
	chassis.moveTo(0, 10, 4000);
	pros::delay(750);
	drive_.move(-80);
	pros::delay(400);
	IntakeMotor.brake();
	drive_.move(-80);
	pros::delay(300);
	drive_.move(110);
	pros::delay(700);
	drive_.move(-80);
	pros::delay(400);
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
				autonName = "Far side defensive";
			}
			if (auton == 2) {
				autonName = "Home side offensive";
			}
			if (auton == 3) {
				autonName = "Skills Challenge";
			}
			if (auton == 4) {
				autonName = "Autonomous tuning";
			}
			// Set the controllet text to the current autonomous routine value
			pros::lcd::print(3, "Autonomous prog: %s", autonName);

	}
	
		
    
}