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

LadyBrown::LadyBrown() : MoveToPointPID(2, 0, 1.25, 2, false), current_state{ANGLE::BASE_STATE}, target_angle{0} {
   LadyBrownMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
   LadyBrownRotation.set_position(0);
}

LadyBrown::ANGLE &operator++(LadyBrown::ANGLE &s) {
   return s = (s == LadyBrown::ANGLE::ATTACK_STATE) ? LadyBrown::ANGLE::BASE_STATE
                                                    : static_cast<LadyBrown::ANGLE>(static_cast<int>(s) + 1);
}

LadyBrown::ANGLE &operator--(LadyBrown::ANGLE &s) {
   return s = (s == LadyBrown::ANGLE::BASE_STATE) ? LadyBrown::ANGLE::BASE_STATE
                                                  : static_cast<LadyBrown::ANGLE>(static_cast<int>(s) - 1);
}

void LadyBrown::run(bool async) {
   if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      LadyBrown::ANGLE new_state = ++current_state;
      if (async) {
         pros::Task task([new_state, this]() { MoveToPoint(new_state); });
      } else {
         MoveToPoint(new_state);
      }
   } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      LadyBrown::ANGLE new_state = --current_state;
      if (async) {
         pros::Task task([new_state, this]() { MoveToPoint(new_state); });
      } else {
         MoveToPoint(new_state);
      }
   }
}

void LadyBrown::MoveToPoint(LadyBrown::ANGLE state, int max_error, int timeout) {
   constexpr int base_angle = 0;
   constexpr int load_angle = -15000;
   constexpr int attack_angle = -15000;
   lemlib::Timer timer(timeout);

   target_angle = LadyBrownRotation.get_position();

   switch (state) {
   case ANGLE::BASE_STATE:
      target_angle = base_angle;
      break;
   case ANGLE::LOAD_STATE:
      target_angle = load_angle;
      break;
   case ANGLE::ATTACK_STATE:
      target_angle = attack_angle;
      break;
   }

   while (true) {
      int error = target_angle - LadyBrownRotation.get_position();
      int current_voltage = LadyBrownMotor.get_voltage();

      // Converting from int to float for LemLib PID
      float motor_voltage = MoveToPointPID.update(static_cast<float>(error));
      motor_voltage = lemlib::slew(motor_voltage, static_cast<float>(current_voltage), 3050);

      if (std::abs(error) < max_error || timer.isDone()) {
         LadyBrownMotor.brake();
         break;
      }

      LadyBrownMotor.move_voltage(static_cast<int>(motor_voltage));
      pros::delay(20);
   }
}
