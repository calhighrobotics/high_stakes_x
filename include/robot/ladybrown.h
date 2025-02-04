#pragma once

#include "lemlib/pid.hpp"
namespace Robot {

/**
 * @brief The LadyBrown class represents the robot lady brown subsystem.
 */
class LadyBrown {
public:
   // The ENUM associates with each location of the rotation sensor for the LadyBrown to move.
   enum class ANGLE { BASE_STATE, LOAD_STATE, ATTACK_STATE };

   void run(bool async = true);

   void MoveToPoint(LadyBrown::ANGLE state, int max_error = 10, int timeout = 10000);

   LadyBrown();

   ANGLE current_state;

   int target_angle;
private:
   lemlib::PID MoveToPointPID;

};
} // namespace Robot