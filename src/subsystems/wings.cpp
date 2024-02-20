#include "robot/wings.h"
#include "api.h"
#include "globals.h"

using namespace Robot::Globals;

void Robot::Wings::run(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        state = !state;
    }
    if (state) {
        wing.set_value(true);
        wing2.set_value(false);
        Robot::Wings::setState(true);
    }
    else {
        wing.set_value(false);
        wing2.set_value(true);
        Robot::Wings::setState(true);
    }
}

void Robot::Wings::setState(bool wingState) {
    state = wingState;
}

bool Robot::Wings::getState() {
    return state;
}