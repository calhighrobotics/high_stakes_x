#include "robot/elevation.h"
#include "api.h"
#include "globals.h"

using namespace Robot::Globals;

void Robot::Elevation::run(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        state = !state;
    }
    if (state) {
        Elevator.set_value(true);
    }
    else {
        Elevator.set_value(false);
    }
}