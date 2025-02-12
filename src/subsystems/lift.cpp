#include "robot/lift.h"
#include "globals.h"
#include "pros/colors.hpp"
#include "pros/rtos.hpp"
#include "robot/auton.h"

constexpr int SLOWER_VELOCITY = 200;
constexpr int FASTER_VELOCITY = 600;

using namespace Robot;
using namespace Robot::Globals;

// Set to skills by default to prevent any accidental ring skips
Lift::ALLIANCE_COLOR Lift::alliance_color = Lift::SKILLS;


Lift::Lift() { 
   //Set to skills by default to prevent any accidental ring skips
   Lift::ring_color = Lift::SKILLS;
   Lift::hookSkipRunning = false;
   colorSensor.set_led_pwm(75);
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
      HookRun();
   } else {
      IntakeMotor.brake();
      HookMotor.brake();
   }
}

void Lift::HookRun() {
   if (colorSensor.get_hue() > 200 && colorSensor.get_hue() < 230) {
      Lift::ring_color = Lift::BLUE;
   } else if (colorSensor.get_hue() > 0 && colorSensor.get_hue() < 30) {
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
   if (!hookSkipRunning) {
      hookSkipRunning = true;
      HookMotor.move_velocity(200);
      if (true) {
         HookMotor.brake();
         pros::delay(100);
         HookMotor.move_relative(100, 200);
      }
   }
   ;
}