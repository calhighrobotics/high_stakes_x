#include "robot/intake.h"
#include "api.h"
#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;



void Intake::score() {
    IntakeMotor.move(100);
    
}

void Robot::Intake::run(){
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		IntakeMotor.move(127);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        IntakeMotor.move(-127);
    }
    else {
        IntakeMotor.brake();
    }
}