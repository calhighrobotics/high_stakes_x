#pragma once

namespace Robot {

/**
 * @brief The Hang class represents a Hanging mechanism.
 */
class Hang {
 public:
   /**
    * @brief Runs Hanging mechanism.
    */
   void run();

   Hang();

   /**
    * @brief Toggles Hang state.
    */
   void toggle();
};
} // namespace Robot