#include "robot/intake.h"
#include "api.h"
#include "globals.h"


void Robot::Intake::run(){
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		Robot::IntakeMotor.move(127);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        Robot::IntakeMotor.move(-127);
    }
    else {
        Robot::IntakeMotor.brake();
    }
}