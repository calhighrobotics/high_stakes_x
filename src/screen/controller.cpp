#include "main.h" // IWYU pragma: export
#include "screen/controller.h"
#include "pros/misc.hpp"
#include "pros/rtos.h"
#include <cstdint>
#include <ctime>

using namespace Robot;
using namespace Robot::Globals;

void Controller::update_battery_status(void* param) {
    double capacity = pros::battery::get_capacity();
    uint32_t now = pros::c::millis();
    bool hasRumbled = false;

    while (true) {
        // Should be less than 30% battery capacity
        if (capacity < 30) {
            controller.print(0, 0, "B LOW: %d", capacity);
            if (!hasRumbled) {
                controller.rumble(". . . . .");
                bool hasRumbled = true;
            }
        }
        else {
            controller.print(0, 0, "B: %d", capacity);
        }
        pros::c::task_delay_until(&now, 60000);
    }
}