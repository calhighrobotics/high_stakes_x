#include "utility/controller.h"
#include "globals.h"
#include "main.h" // IWYU pragma: export
#include "pros/device.hpp"
#include "pros/rtos.h"
#include <cstdint>
#include <sstream>

using namespace Robot;
using namespace Robot::Globals;

void Controller::notify_motor_disconnect(void *param) {
   std::vector<pros::Device> all_motors = pros::Device::get_all_devices(pros::DeviceType::motor);
   std::vector<unsigned short int> disconnected;
   std::vector<unsigned short int> last_disconnected;
   uint32_t now = pros::c::millis();

   const int SECOND = 1000;

   while (true) {
      std::stringstream disc_motors;

      for (pros::Device &i : all_motors) {
         if (!i.is_installed()) {
            disconnected.push_back(i.get_port());
         }
      }
      if (disconnected.size() > last_disconnected.size()) {
         controller.rumble(". . .");
      }
      if (disconnected.size() < last_disconnected.size()) {
         controller.rumble("_");
      }

      std::copy(disconnected.begin(), disconnected.end(), std::ostream_iterator<int>(disc_motors, " "));
      controller.set_text(0, 0, disc_motors.str());
      disconnected = last_disconnected;
      disconnected.clear();
   }
   pros::c::task_delay_until(&now, SECOND);
}