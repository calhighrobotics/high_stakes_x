#include "robot/intake.h"
#include "globals.h"
#include "pros/colors.h"
#include "pros/vision.h"
#include "pros/vision.hpp"
#include "robot/auton.h"

using namespace Robot;
using namespace Robot::Globals;

using namespace pros::v5;

Intake::Intake() {
   elevated = false;
   alliance_color = false;
   colorSensor.set_led(pros::c::COLOR_WHITE);
   controller.print(0, 0, "Intake initialized");
   // Color sensor - store signatures to the sensor
   colorSensor.set_signature(0, &RED_SIG);
   colorSensor.set_signature(1, &BLUE_SIG);
   colorSensor.set_signature(2, &BLUE_DARK_SIG);

   // Set the color code for blue
   pros::vision_color_code_t blue_color_code = colorSensor.pros::v5::Vision::create_color_code(1, 2, 0, 0, 0);
}

void Intake::run() {

   if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      IntakeMotor.move_velocity(-600);
      HookMotor.move_velocity(-350);
      if (checkStop()) {
         controller.rumble("...");
         IntakeMotor.move_relative(-100, -600);
         HookMotor.move_relative(-100, -350);
      }
   } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      IntakeMotor.move_velocity(600);
      HookMotor.move_velocity(350);
   } else {
      IntakeMotor.brake();
      HookMotor.brake();
   }
}


void Intake::toggle() { elevated = !elevated; }

// Vision sensor only works with intake, therefore it should not on
bool Intake::checkStop() {
   pros::vision_object_s_t blueRing = colorSensor.get_by_code(0, blue_color_code);
   pros::vision_object_s_t redRing = colorSensor.get_by_sig(0, 0);

   if (blueRing.width * blueRing.height > redRing.width * redRing.height) {
      if (Autonomous::auton > 0) {
         return true;
      }
      return false;
   }
   else if (redRing.width * redRing.height > blueRing.width * blueRing.height) {
      if (Autonomous::auton < 0) {
         return true;
      }
      return false;
   }
   else {
      return false;
   }
}
