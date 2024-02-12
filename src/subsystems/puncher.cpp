#include "robot/drivetrain.h"
#include "api.h"
#include "globals.h"
#include "pros/apix.h"

using namespace Robot;




void Puncher::run() {

    

    if (Puncher.toShoot() == 2 && distancePuncher == false) {
        if(controller.get_digital(DIGITAL_R2)) {
            PuncherMotor.move(95);
            PuncherMotor2.move(95);
        }
        else {
            PuncherMotor.brake();
            PuncherMotor2.brake();
        }
    }

    if k
    
   
}

int Puncher::toShoot() {
    if (pros::c::registry_get_plugged_type(13) == pros::c::E_DEVICE_DISTANCE) {
        distancePuncher = false;
        return 2;
    }
    if (distance.get() <= 12) {
        distancePuncher = true;
        return 1;
    }
    if (distance.get() > 12) {
        distancePuncher = true;
        return 0;
    }
}