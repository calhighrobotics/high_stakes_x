#pragma once
#include "pros/apix.h" // IWYU pragma: export
#include "robot/auton.h"

namespace Robot {

/**
 * @brief The logger screen displays current drive information on the screen.
 */
class logger_screen {

public:
   /**
    * @brief Constructor.
    */
   logger_screen();

   /**
    * @brief Function ceates the logger screen in driver and autonomous modes.
    */
   void log();

private:
   void display_update(lv_event_t *e);
};
} // namespace Robot