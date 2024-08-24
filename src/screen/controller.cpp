#include "screen/controller.h"
#include "main.h" // IWYU pragma: export
#include "pros/misc.hpp"
#include "pros/rtos.h"
#include <cstdint>
#include <ctime>

using namespace Robot;
using namespace Robot::Globals;

void Controller::update_battery_status(void *param) {
   double capacity = pros::battery::get_capacity();
   uint32_t now = pros::c::millis();
   bool hasRumbled = false;
   const int LOW_BATTERY = 30;
   const int MINUTE = 60000;

   while (true) {
      if (capacity < LOW_BATTERY) {
         controller.print(0, 0, "B LOW: %d", capacity);
         if (!hasRumbled) {
            controller.rumble(". . . . .");
            bool hasRumbled = true;
         }
      } else {
         controller.print(0, 0, "B: %d", capacity);
      }
      pros::c::task_delay_until(&now, MINUTE);
   }
}