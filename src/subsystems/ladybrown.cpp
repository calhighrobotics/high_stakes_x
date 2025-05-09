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

LadyBrown::LadyBrown() : MoveToPointPID(2, 0, 0, 2, false), ActiveBrakePID(0.8, 0, 1, 6, true) {
   LadyBrownRotation.set_position(0);
   bool manualControl = false;
   LadyBrownMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}


void LadyBrown::run(bool async, int timeout) {
   LADYBROWN_STATE move_to;

   if (!isPIDRunning) {      

      if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
         LadyBrown::isPIDRunning = false;
         LadyBrownMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

         //delay to exit the previous PID inside this control flow
         pros::delay(50);
         manualControl = true;
         LadyBrownMotor.move_velocity(-200);

         if (LadyBrownRotation.get_position() > -10000) {
            LadyBrown::brake_target = LadyBrownRotation.get_position() - 4500;
         } else {
            LadyBrown::brake_target = LadyBrownRotation.get_position() - 2300;
         }

      }
      else {
         if (!manualControl) {
            LadyBrownMotor.move_velocity(0);
         } else {
            LadyBrownMotor.move_voltage(ActiveBrakePID.update(LadyBrown::brake_target - LadyBrownRotation.get_position()));
         }
      }
   } 
   
   if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      LadyBrown::isPIDRunning = false;
      LadyBrownMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      manualControl = false;
      //delay to exit the previous PID inside this control flow
      pros::delay(50);

      if (current_state == BASE_STATE) {
         move_to = LOAD_STATE;
      } else {
         move_to = BASE_STATE;
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
   constexpr double load_location = -1900;
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
      case LADYBROWN_STATE::SIZECHECK_STATE:
         target = -12550;
         break;
      }

      std::cout << "target: " << target << std::endl;

      MoveToPointPID.reset();

      lemlib::Timer timer(timeout);

      while (LadyBrown::isPIDRunning == true) {
         double error = target - LadyBrownRotation.get_position();
         double motor_voltage = MoveToPointPID.update(error);

         // motor_voltage = lemlib::slew(motor_voltage, LadyBrownMotor.get_voltage(), 1500);

         if (std::abs(error) < max_error || timer.isDone()) {
            LadyBrownMotor.brake();
            LadyBrown::isPIDRunning = false;
            LadyBrown::current_state = state;
            break;
         }

         LadyBrownMotor.move_voltage(motor_voltage);
         LadyBrown::isPIDRunning = true;

         if (!LadyBrown::isPIDRunning) {
            return;
         }

         pros::delay(20);
      }
   }
}
