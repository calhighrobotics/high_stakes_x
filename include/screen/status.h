#pragma once

namespace Robot {

/**
 * @brief The Latch class represents a latching mechanism.
 * @todo Implement the Robot driving status screen, with graphs of heading,
 * latitude, longitude, etc.
 */
class status_screen {
 public:
   /**
    * @brief Runs latching mechanism.
    */

   status_screen();

   /**
    * @brief Toggles latch state.
    */
   void status();
};
} // namespace Robot