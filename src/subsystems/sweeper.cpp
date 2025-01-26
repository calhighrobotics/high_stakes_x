#include "robot/sweeper.h"

#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;

void Sweeper::run() {
   if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      SweeperControl.toggle();
   }
}

Sweeper::Sweeper() { ; }

void Sweeper::toggle() { SweeperControl.toggle(); }
