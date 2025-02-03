#pragma once
#include "lemlib/api.hpp"

namespace Robot {

/**
 * @brief The Intake class represents a robot intake system.
 */
class LadyBrown {
public:
   // The ENUM associates with each location of the rotation sensor for the LadyBrown to move.
   enum LADYBROWN_STATE { BASE_STATE = 1, LOAD_STATE = 2, ATTACK_STATE = 3 };

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

   void MoveToPoint();

   LADYBROWN_STATE current_state;

   double target;

private:
   /**
    * @brief blue is false, red is true.
    */
   bool alliance_color;

};
} // namespace Robot