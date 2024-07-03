#include "robot/intake.h"
#include "api.h"
#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;





void Intake::score() {
    IntakeMotor.move(100);
    
}

void Intake::run(unsigned short direction) {
    switch (direction) {
        case 0:
            IntakeMotor.move(-127);
            break;
        case 1:
            IntakeMotor.move(127);
            break;
        default:
            IntakeMotor.move(0);
    }

}