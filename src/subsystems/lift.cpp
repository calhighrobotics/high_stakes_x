#include "robot/lift.h"
#include "globals.h"
#include "pros/colors.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "robot/auton.h"
#include <iostream>

constexpr int SLOWER_VELOCITY = 200;
constexpr int FASTER_VELOCITY = 600;
// Rough estimate of the number of degrees the hook turns for a full cycle, measured by the rotation sensor
constexpr int REVOLUITION_DEGREES = 450;

using namespace Robot;
using namespace Robot::Globals;

// Ring stop position: 41256
// Full revolution: 83540

// Set to skills by default to prevent any accidental ring skips
Lift::ALLIANCE_COLOR Lift::alliance_color = Lift::SKILLS;
bool Lift::ringSkipActive = true;


Lift::Lift() { 
   //Set to skills by default to prevent any accidental ring skips
   Lift::ring_color = Lift::SKILLS;
   Lift::hookSkipRunning = false;
   HookMotor.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_COAST);
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

   if (colorSensor.get_hue() > 195 && colorSensor.get_hue() < 230) {
      Lift::ring_color = Lift::BLUE;
   } else if (colorSensor.get_hue() > 12 && colorSensor.get_hue() < 30) {
      Lift::ring_color = Lift::RED;
   }



   if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      Lift::hookSkipRunning = false;

      IntakeMotor.move_velocity(-FASTER_VELOCITY);
      HookMotor.move_velocity(-SLOWER_VELOCITY);
   } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      while (HookRotation.get_position() % 83540 < 7000) {
         HookMotor.move_velocity(200);
      }
      HookMotor.brake();
      pros::delay(800);
      while (HookRotation.get_position() % 83540 > 7000 && HookRotation.get_position() % 83540 < 53540) {
         HookMotor.move_velocity(200);
      }
      HookMotor.brake();
      // IntakeMotor.move_velocity(FASTER_VELOCITY);
      // if (ringSkipActive) {
      //    //HookRun();
      //    if ((HookRotation.get_position() % 84040) > 10000 && (HookRotation.get_position() % 84040) < 14000) {
      //       HookMotor.brake();
      //       pros::delay(500);
      //       HookMotor.move_velocity(SLOWER_VELOCITY);
      //    }
      //    HookMotor.move_velocity(SLOWER_VELOCITY);


      // } else {
      //    HookMotor.move_velocity(SLOWER_VELOCITY);
      // }
   }  else {
      IntakeMotor.brake();
      HookMotor.brake();
   }
   
   //std::cout << "Ring Color: " << Lift::ring_color << "Hook velocity" << HookMotor.get_target_velocity() << std::endl;
}

void Lift::HookRun() {
   if (colorSensor.get_hue() > 195 && colorSensor.get_hue() < 230) {
      Lift::ring_color = Lift::BLUE;
   } else if (colorSensor.get_hue() > 12 && colorSensor.get_hue() < 30) {
      Lift::ring_color = Lift::RED;
   }

   pros::Task move([&]() { HookSkip(); }, "HookSkip");

   // if (!Lift::hookSkipRunning) {
   //    Lift::hookSkipRunning = true;

   //    if ((Lift::ring_color != Lift::alliance_color) && Lift::alliance_color != Lift::SKILLS) {
   //       pros::Task move([&]() { HookSkip(); }, "HookSkip");

   //    }
   //    else {
   //       HookMotor.move_velocity(200);
   //    }
   // }


}

void Lift::HookSkip() {
   while(true) {
      while (HookRotation.get_position() % 83540 < 41256) {
         HookMotor.move_velocity(200);
      }
      HookMotor.brake();
      pros::delay(200);
   }
}