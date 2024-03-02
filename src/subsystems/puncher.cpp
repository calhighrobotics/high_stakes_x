#include "robot/drivetrain.h"
#include "robot/puncher.h"
#include "api.h"
#include "globals.h"
#include "pros/apix.h"

using namespace Robot;
using namespace Robot::Globals;


void Puncher::UserRun() {
    if (toShoot() == 2) {
        Puncher::distancePuncherBool = 1;
    }
    // Manual Puncher Control
    if (Puncher::distancePuncherBool == 1) {
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            punchers.move(127);
        }
        else {
            punchers.brake();
        }
    }  
}

void Puncher::DistanceRun() {

    if (Puncher::toShoot() == 2) {
        Puncher::distancePuncherBool = 1;
    }

    if (Puncher::distancePuncherBool == 0) {
    // Distance Puncher Control
        if (distance.get() <= 20) {
        
            // if (Puncher::toShoot() == 1) {
            punchers.move(127);
            }
        else {
            punchers.brake();
        }
    }
    else {
        Puncher::UserRun();
    }
}

void Puncher::run() {
    if (Puncher::distancePuncherBool == 0) {
        Puncher::DistanceRun();
    }
    else {
        Puncher::UserRun();
    }

}

int Puncher::toShoot() {
    if (distance.get() <= 20) {
        return 1;
    }
    if (distance.get() > 20) {
        return 0;
    }
    return 0;
}

Puncher::Puncher() {
    Puncher::distancePuncherBool = 0;
}

void Puncher::PuncherSwitch() {

    if(puncherToggleSwitch.get_new_press()) {
        pros::lcd::clear_line(1);

        Puncher::distancePuncherBool = Puncher::distancePuncherBool + 1;
        
        if (Puncher::distancePuncherBool == 2) {
            Puncher::distancePuncherBool = 0;
        }

        std::printf("Puncher: %d\n", Puncher::distancePuncherBool);
        
        if (Puncher::distancePuncherBool == 0) {
            pros::lcd::set_text(1, "Distance puncher on!");
        }
        if (Puncher::distancePuncherBool == 1) {
            pros::lcd::set_text(1, "Distance puncher off!");
        }
    }		
    
}

void Puncher::ManualOverride() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        Puncher::distancePuncherBool = Puncher::distancePuncherBool + 1;
        
        if (Puncher::distancePuncherBool == 2) {
            Puncher::distancePuncherBool = 0;
        }

        std::printf("Puncher: %d\n", Puncher::distancePuncherBool);
        
        if (Puncher::distancePuncherBool == 0) {
            controller.print(0, 0, "Dist. punch on");
        }
        if (Puncher::distancePuncherBool == 1) {
            controller.print(0, 0, "Dist. punch off");
        }
    }
}