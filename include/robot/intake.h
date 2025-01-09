#pragma once

namespace Robot {

/**
 * @brief The Intake class represents a robot intake system.
 */
class Intake {
public:
   /**
    * @brief Runs the main function of the intake system.
    *
    * Takes optional user input to control the direction of the intake system in
    * autonomous.
    */
   void run();

   /**
    * @brief Checks whether the intake should stop to skip the ring depending on color.
    * It's the embodiment of vision sensor usage in this codebase.
    */
   void checkStop();

   Intake();

   /**
    * @brief Toggles intake elevation.
    */
   void toggle();

private:
   bool elevated;

   /**
    * @brief blue is false, red is true.
    */
   bool alliance_color;

   /**
    * @brief Runs the hook subsystem.
    * This function checks if a ring is present near the hook using a limit
    * switch before activating it for one revolution.
    */

   void spinHook();
};
} // namespace Robot