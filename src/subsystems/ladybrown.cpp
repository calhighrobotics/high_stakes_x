#include "robot/ladybrown.h"
#include <cstdlib>
#include "globals.h"
#include "lemlib/pid.hpp"
#include "lemlib/timer.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"

using namespace Robot;
using namespace Robot::Globals;


LadyBrown::LADYBROWN_STATE LadyBrown::current_state = LadyBrown::BASE_STATE;

LadyBrown::LadyBrown() : MoveToPointPID(2, 0, 0, 2, false) {
   LadyBrownRotation.set_position(0);
   LadyBrownMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void LadyBrown::run(bool async, int timeout) {
   LADYBROWN_STATE move_to = LadyBrown::current_state;

   if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      if (current_state == BASE_STATE) {
         move_to = LOAD_STATE;
      } else if (current_state == LOAD_STATE) {
         move_to = ATTACK_STATE;
      } else {
         move_to = BASE_STATE;
      }
      std::cout << "Moving to: " << move_to << std::endl;
      std::cout << "current state: " << current_state << std::endl;


      if (!async) {
         MoveToPoint(move_to);
      } else {

         pros::Task move([move_to, this]() { MoveToPoint(move_to); });
      }

      current_state = move_to;

   } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {

      if (current_state == ATTACK_STATE) {
         move_to = LOAD_STATE;
      } else if (current_state == LOAD_STATE) {
         move_to = BASE_STATE;
      } else {
         return;
      }

      std::cout << "Moving to: " << move_to << std::endl;
      std::cout << "current state: " << current_state << std::endl;


      if (!async) {
         MoveToPoint(move_to);
      } else {
         pros::Task move([move_to, this]() { MoveToPoint(move_to); }, "LadyBrownMove");
      }


      current_state = move_to;
   }
}

int LadyBrown::get_target() {
   return target;
}

void LadyBrown::MoveToPoint(LADYBROWN_STATE state, int max_error, int timeout) {
   
   

   std::cout << "state: " << current_state << std::endl;
   constexpr double base_location = 30;
   constexpr double load_location = -2500;
   constexpr double attack_location = -13000;

   int target = LadyBrownRotation.get_position();

   switch (state) {
   case LADYBROWN_STATE::BASE_STATE:
      target = base_location;
      break;
   case LADYBROWN_STATE::LOAD_STATE:
      target = load_location;
      break;
   case LADYBROWN_STATE::ATTACK_STATE:
      target = attack_location;
      break;
   }

   
   std::cout << "target: " << target << std::endl;

   MoveToPointPID.reset();

   timer.set(timeout);

   while (true) {
      double error = target - LadyBrownRotation.get_position();
      double motor_voltage = MoveToPointPID.update(error);

      //motor_voltage = lemlib::slew(motor_voltage, LadyBrownMotor.get_voltage(), 1500);

      if (std::abs(error) < max_error || timer.isDone()) {
         LadyBrownMotor.brake();
         break;
      }

      LadyBrownMotor.move_voltage(motor_voltage);
      pros::delay(20);
   }
}