#pragma once

namespace Robot {

/**
 * @brief The Intake class represents a robot intake system.
 */
class LadyBrown {
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
    * It is the embodiment of vision sensor usage in this codebase.
    */
   void checkStop();

   LadyBrown();

   LadyBrown(double kP, double kI, double kD);

   double pid_update();

   /**
    * @brief Toggles intake elevation.
    */
   void toggle();

 private:
    double kP;
    double kI;
    double kD;

   /**
    * @brief blue is false, red is true.
    */
   bool alliance_color;
};
} // namespace Robot