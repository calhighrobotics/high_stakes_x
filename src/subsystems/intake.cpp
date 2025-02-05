#include "robot/intake.h"

#include "globals.h"

#define SLOWER_VELOCITY 200
#define FASTER_VELOCITY 600

using namespace Robot;
using namespace Robot::Globals;

Intake::Intake() {
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

