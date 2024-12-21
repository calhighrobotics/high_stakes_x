#include "robot/latch.h"

#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;

void Sweeper::run() {
   if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
      SweeperControl.toggle();
   }
}

Sweeper::Sweeper() { ; }
