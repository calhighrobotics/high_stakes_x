#pragma once

#include "auton.h"
#include "drivetrain.h"

namespace Robot {
/**
 * @brief Contains utility functions for controlling the screen and toggling
 * subsystems.
 * @todo Deprecate Utility class due to its purpose being covered by the screen
 * class.
 * @warning Try not to use this class as much as possible. The screen class is a
 * better alternative.
 * @test The Utility namespace is a group of unrelated methods that have
 * functions that are important independently.
 */
namespace Utility {
/// @brief Displays current position of the robot.
void displayLocation();
/// @brief Displays current velocity of the robot.
void displayMotorVel();

}  // namespace Utility
}  // namespace Robot
