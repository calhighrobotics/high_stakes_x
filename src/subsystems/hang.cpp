#include "robot/hang.h"

#include "globals.h"
#include "pros/misc.h"

using namespace Robot;
using namespace Robot::Globals;

void Hang::run() {
   if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      Hang::toggle();
   }
}

Hang::Hang() { ; }

void Hang::toggle() { HangControl.toggle(); }