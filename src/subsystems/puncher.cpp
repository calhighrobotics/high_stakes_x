#include "robot/drivetrain.h"
#include "robot/puncher.h"
#include "api.h"
#include "globals.h"
#include "pros/apix.h"

using namespace Robot;
using namespace Robot::Globals;

void Puncher::setDistancePuncher(bool punch) {
    distancePuncher = punch;
}


void Puncher::run(int autonVal) {

    // Manual Puncher Control
    if (Puncher::toShoot() == 2 || distancePuncher == false) {
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            punchers.move(127);
        }
        else {
            punchers.brake();
        }
    }

    // Auton Puncher Control using the distance sensor
    if (distancePuncher == true && autonVal == 3) {
        if (Puncher::toShoot() == 0) {
            punchers.move_absolute(30, 95);
        }
        else {
            punchers.brake();
        }
    }
    
   
}

int Puncher::toShoot() {
    if (pros::c::registry_get_plugged_type(13) != pros::c::E_DEVICE_DISTANCE) {
        distancePuncher = false;
        return 2;
    }
    if (distance.get() <= 12 && distancePuncher == true) {
        return 1;
    }
    if (distance.get() > 12 && distancePuncher == true) {
        return 0;
    }
    return 2;
}


void Puncher::PuncherSwitch() {

        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
			
			// Toggles the puncher distance sensor
            Puncher::setDistancePuncher(!distancePuncher);


            // Prints the state of the puncher distance sensor to the brain(as a boolean)
            if (distancePuncher == true) {
                controller.print(0, 0, "Puncher: True");
            }
            else {
                controller.print(0, 0, "Puncher: False");
            }
           

		}
	
		
    
}