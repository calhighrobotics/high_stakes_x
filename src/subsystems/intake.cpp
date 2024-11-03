#include "robot/intake.h"

#include "globals.h"

#define SLOWER_VELOCITY 375
#define FASTER_VELOCITY 600

using namespace Robot;
using namespace Robot::Globals;

Intake::Intake() {
   elevated = false;
   alliance_color = false;
}

void Intake::run() {

   if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      IntakeMotor.move_velocity(-FASTER_VELOCITY);
      HookMotor.move_velocity(-SLOWER_VELOCITY);
   } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      IntakeMotor.move_velocity(FASTER_VELOCITY);
      HookMotor.move_velocity(SLOWER_VELOCITY);
   } else {
      IntakeMotor.brake();
      HookMotor.brake();
   }
}

void Intake::toggle() { elevated = !elevated; }

// Vision sensor only works with intake, therefore it should not on
void Intake::checkStop() {}
