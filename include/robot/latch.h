#pragma once

namespace Robot {

/**
 * @brief The Latch class represents a latching mechanism.
 */
class Latch {
 public:
   /**
    * @brief Runs latching mechanism.
    */
   void run();

   Latch();

   /**
    * @brief Toggles latch state.
    */
   void toggle();
};
} // namespace Robot