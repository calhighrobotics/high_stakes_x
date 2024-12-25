#include "robot/ladybrown.h"

#include "globals.h"
#include "pros/motors.h"

#define SLOWER_VELOCITY 125
#define FASTER_VELOCITY 150

using namespace Robot;
using namespace Robot::Globals;

LadyBrown::LadyBrown(double kP, double kI, double kD) {
    LadyBrownMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void LadyBrown::run() {

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        LadyBrownMotor.move_velocity(-SLOWER_VELOCITY);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        LadyBrownMotor.move_velocity(SLOWER_VELOCITY);
    } else {
        LadyBrownMotor.brake();
    }
}

void LadyBrown::toggle() {}

// Vision sensor only works with LadyBrown, therefore it should not on
double LadyBrown::pid_update() {
    return 0;
}