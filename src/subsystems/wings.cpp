#include "robot/wings.h"
#include "api.h"
#include "globals.h"

using namespace Robot::Globals;

void Robot::Wings::run(){
    BackWings();
    FrontWings();
}


void Robot::Wings::BackWings() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        BackWingState = !BackWingState;
    }
    if (BackWingState) {
        BackWing1.set_value(true);
        BackWing2.set_value(true);
    }
    else {
        BackWing1.set_value(false);
        BackWing2.set_value(true);
    }
}

void Robot::Wings::FrontWings() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        FrontWingState = !FrontWingState;
    }
    if (FrontWingState) {
        FrontWing.set_value(true);

    }
    else {
        FrontWing.set_value(false);
    }
}

