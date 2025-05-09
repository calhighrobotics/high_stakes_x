#include "robot/intake.h"

#include "globals.h"
#include "lemlib/timer.hpp"
#include "pros/misc.h"
#include "robot/ladybrown.h"
#include "pros/rtos.hpp"

#define SLOWER_VELOCITY 200
#define FASTER_VELOCITY 600

using namespace Robot;
using namespace Robot::Globals;

Intake::Intake() { alliance_color = false; }

lemlib::PID crap_pid(0.3, 0, 0.5, 3, false);

Robot::LadyBrown ladybrown;



void Intake::run() {

   if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      IntakeMotor.move_velocity(-FASTER_VELOCITY);
      HookMotor.move_velocity(-SLOWER_VELOCITY);
   } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      IntakeMotor.move_velocity(FASTER_VELOCITY);
      HookMotor.move_velocity(SLOWER_VELOCITY);

      // if (HookSwitch.get_value() == 1) {
      //    int target = HookRotation.get_position();
      //    while (HookSwitch.get_value() == 1) {
      //       HookMotor.move_velocity(75);
      //       target = HookRotation.get_position() + 16500;
      //       pros::delay(5);
      //    }
         
      //    while (HookRotation.get_position() % 83400 > 41700) {
      //       pros::delay(5);
      //    }
      //    pros::Task move([&]() { ladybrown.MoveToPoint(LadyBrown::ATTACK_STATE); }, "LadyBrownMove");
         
         
      //    HookMotor.move_velocity(-200);
      //    IntakeMotor.move_velocity(0);

      // }
      
   } else {
      IntakeMotor.brake();
      HookMotor.brake();
   }
   
   
   if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      IntakeMotor.move_velocity(FASTER_VELOCITY);
   } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      IntakeMotor.move_velocity(-FASTER_VELOCITY);
   }

   if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      IntakeLift.toggle();
   }
}
