#include "robot/ladybrown.h"
#include "globals.h"
#include "lemlib/pid.hpp"
#include "lemlib/timer.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <cstdlib>

using namespace Robot;
using namespace Robot::Globals;

LadyBrown::LADYBROWN_STATE LadyBrown::current_state = LadyBrown::BASE_STATE;

LadyBrown::LadyBrown() : MoveToPointPID(2, 0, 0, 2, false) {
   LadyBrownRotation.set_position(0);
   LadyBrownMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void LadyBrown::run(bool async, int timeout) {
   LADYBROWN_STATE move_to;

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

      if (!isPIDRunning) {
         current_state = move_to;
      }

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

      if (!isPIDRunning) {
         current_state = move_to;
      }
   }
}

int LadyBrown::get_target() { return target; }

void LadyBrown::MoveToPoint(LADYBROWN_STATE state, int max_error, int timeout) {

   std::cout << "state: " << current_state << std::endl;
   constexpr double base_location = 30;
   constexpr double load_location = -2550;
   constexpr double attack_location = -15500;

   int target;

   std::cout << "state: " << state << std::endl;
   std::cout << "pid: " << isPIDRunning << std::endl;

   if (!isPIDRunning) {

      std::cout << "inner pid: " << isPIDRunning << std::endl;
      LadyBrown::isPIDRunning = true;

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

      lemlib::Timer timer(timeout);

      while (true) {
         double error = target - LadyBrownRotation.get_position();
         double motor_voltage = MoveToPointPID.update(error);

         // motor_voltage = lemlib::slew(motor_voltage, LadyBrownMotor.get_voltage(), 1500);

         if (std::abs(error) < max_error || timer.isDone()) {
            LadyBrownMotor.brake();
            LadyBrown::isPIDRunning = false;
            break;
         }

         LadyBrownMotor.move_voltage(motor_voltage);
         LadyBrown::isPIDRunning = true;
         pros::delay(20);
      }
   }
}