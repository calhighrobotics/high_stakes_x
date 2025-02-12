#pragma once

namespace Robot {

/**
 * @brief The Latch class represents a latching mechanism.
 */
class Sweeper {
public:
   /**
    * @brief Runs sweeper
    */
   void run();

   /**
    * @brief Toggles sweeper state.
    */
   void toggle();

   Sweeper();
};
} // namespace Robot