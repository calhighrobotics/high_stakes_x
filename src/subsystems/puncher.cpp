#include "robot/drivetrain.h"
#include "api.h"
#include "globals.h"
#include "pros/apix.h"

using namespace Robot;


void Puncher::setDistancePuncher(bool punch) {
    distancePuncher = punch;
    if (punch) {
        controller.set_text(0, 0, "Auton Puncher Activated");
    }
    if (!punch) {
        controller.set_text(0, 0, "Auton Puncher Deactivated");
    }
}


void Puncher::run() {

    // Manual Puncher Control
    if (Puncher::toShoot() == 2 || distancePuncher == false) {
        if(controller.get_digital(DIGITAL_R2)) {
            punchers.move(127);
        }
        else {
            punchers.brake();
        }
    }

    // Auton Puncher Control using the distance sensor
    if (Robot::Autonomous::auton == 3 || distancePuncher == true) {
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
}