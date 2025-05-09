#pragma once

#include "lemlib/pid.hpp"
namespace Robot {

/**
 * @brief The LadyBrown class represents the robot lady brown subsystem.
 */
class LadyBrown {
public:
   // The ENUM associates with each location of the rotation sensor for the LadyBrown to move.
   enum LADYBROWN_STATE { BASE_STATE = 1, LOAD_STATE = 2, ATTACK_STATE = 3, SIZECHECK_STATE = 4 };

   void run(bool async = true, int timeout = 1000);

   void MoveToPoint(LadyBrown::LADYBROWN_STATE state, int max_error = 150, int timeout = 1000);

   LadyBrown();

   int get_target();

private:
   lemlib::PID MoveToPointPID;

   lemlib::PID ActiveBrakePID;

   int brake_target;

   static LADYBROWN_STATE current_state;

   int target;

   bool isPIDRunning;

   bool manualControl;
};
} // namespace Robot