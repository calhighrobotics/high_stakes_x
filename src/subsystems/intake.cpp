#include "robot/intake.h"

#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;

Intake::Intake() {
   elevated = false;
   alliance_color = false;
   controller.print(0, 0, "Intake initialized");
}

void Intake::run() {
   if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      IntakeMotor.move_velocity(-375);
      HookMotor.move_velocity(-600);
   } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      IntakeMotor.move_velocity(375);
      HookMotor.move_velocity(600);
   } else {
      IntakeMotor.brake();
      HookMotor.brake();
   }
}

void Intake::toggle() {
   elevated = !elevated;
   IntakeToggle.toggle();
}

void Intake::score() { ; }