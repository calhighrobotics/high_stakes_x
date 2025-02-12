#pragma once

namespace Robot {

/**
 * @brief The Intake class represents a robot intake system.
 */
class Lift {
public:

   enum ALLIANCE_COLOR { RED, BLUE, SKILLS };

   static ALLIANCE_COLOR alliance_color;

   /**
    * @brief Runs the main function of the intake system.
    *
    * Takes optional user input to control the direction of the intake system in
    * autonomous.
    */
   void run();

   void HookRun();

   void HookSkip();

   Lift();

private:
   bool hookSkipRunning;

   ALLIANCE_COLOR ring_color;

   /**
    * @brief blue is false, red is true.
    */
};
} // namespace Robot