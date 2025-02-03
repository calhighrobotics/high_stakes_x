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

   LADYBROWN_STATE current_state;

   double target;

   //True for going upwards, false for going downwards. This helps with the toggler.
   bool direction;

   void run();

   void MoveToPoint(LadyBrown::LADYBROWN_STATE state, int timeout);

   LadyBrown();

private:
   /**
    * @brief blue is false, red is true.
    */
   bool alliance_color;

   lemlib::PID MoveToPointPID;

};
} // namespace Robot