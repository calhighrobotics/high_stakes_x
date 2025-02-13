#include "robot/lift.h"
#include "globals.h"
#include "pros/colors.hpp"
#include "pros/rtos.hpp"
#include "robot/auton.h"

constexpr int SLOWER_VELOCITY = 200;
constexpr int FASTER_VELOCITY = 600;
// Rough estimate of the number of degrees the hook turns for a full cycle, measured by the rotation sensor
constexpr int REVOLUITION_DEGREES = 450;

using namespace Robot;
using namespace Robot::Globals;

// Set to skills by default to prevent any accidental ring skips
Lift::ALLIANCE_COLOR Lift::alliance_color = Lift::SKILLS;
bool Lift::ringSkipActive = true;


Lift::Lift() { 
   //Set to skills by default to prevent any accidental ring skips
   Lift::ring_color = Lift::SKILLS;
   Lift::hookSkipRunning = false;
   colorSensor.set_led_pwm(75);
   HookRotation.set_position(0);

 }

void Lift::run() {

   if (static_cast<int>(Autonomous::auton) < 0) {
      Lift::alliance_color = Lift::BLUE;
   }
   else if (static_cast<int>(Autonomous::auton) > 0) {
      alliance_color = Lift::RED;
   }
   else {
      alliance_color = Lift::SKILLS;
   }


   if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      IntakeMotor.move_velocity(-FASTER_VELOCITY);
      HookMotor.move_velocity(-SLOWER_VELOCITY);
   } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      IntakeMotor.move_velocity(FASTER_VELOCITY);
      if (ringSkipActive) {
         HookMotor.move_velocity(SLOWER_VELOCITY);
      } else {
         HookMotor.move_velocity(SLOWER_VELOCITY);
      }
   } else {
      IntakeMotor.brake();
      HookMotor.brake();
   }
}

void Lift::HookRun() {
   if (colorSensor.get_hue() > 195 && colorSensor.get_hue() < 230) {
      Lift::ring_color = Lift::BLUE;
   } else if (colorSensor.get_hue() > 12 && colorSensor.get_hue() < 30) {
      Lift::ring_color = Lift::RED;
   }

   if ((Lift::ring_color != Lift::alliance_color) && Lift::alliance_color != Lift::SKILLS) {
      pros::Task move([&]() { HookSkip(); }, "HookSkip");

   }
   else {
      HookMotor.move_velocity(200);
   }


}

void Lift::HookSkip() {
   while (HookRotation.get_position() % 450 < 135 && HookRotation.get_position() % 450 > 165) {
      int current_position = HookRotation.get_position() % 450;
      HookMotor.move_velocity(200);
   }
   HookMotor.brake();
   pros::delay(100);
   HookMotor.move_relative(100, 200);
}