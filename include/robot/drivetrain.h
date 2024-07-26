// Header guard - Ensures that the header file will not get double imported.
#pragma once
#include <string>

/**
 * @file drivetrain.h
 * @brief Contains the declaration of the Drivetrain class.
 */

namespace Robot {

/**
 * @class Drivetrain
 * @brief Represents the drivetrain of the robot.
 *
 * The Drivetrain class is responsible for controlling the movement of the
 * robot's drivetrain. It provides functions to interpret joystick inputs and
 * convert them into appropriate drivetrain movements. The drivetrain can be
 * controlled using different drive modes, such as tank drive or arcade drive.
 *
 * The Drivetrain class also allows setting and retrieving the deadzone value
 * for the joystick. The deadzone is a range around the joystick's resting
 * position where no movement is registered. By adjusting the deadzone value,
 * the sensitivity of the joystick inputs can be fine-tuned.
 */
class Drivetrain {
 public:
  /**
   * @brief Runs the drivetrain.
   *
   * This function is responsible for controlling the movement of the robot's
   * drivetrain. It executes the necessary actions to make the robot move
   * according to the current drive mode.
   *
   * @details The drivetrain can be controlled using different drive modes, such
   * as tank drive or arcade drive. This function implements the logic to
   * interpret the joystick inputs and convert them into appropriate drivetrain
   * movements.
   */
  void run();

  /**
   * @brief Switches the DriveTrain mode between arcade and tank drive.
   *
   * The drive mode determines how the drivetrain interprets the joystick
   * inputs. Arcade drive uses the left joystick for forward and backward
   * movement, and the right joystick for left and right movement. Tank drive
   * uses the left and right joysticks for controlling the left and right sides
   * of the robot.
   */
  ///< The current drive train mode, between arcade (0) and tank (1).

  /**
   * @brief Switches the drive mode of the robot.
   *
   * This function takes an integer parameter `drive` representing the desired
   * drive mode and returns a string. The drive mode determines how the robot's
   * drivetrain operates.
   *
   * @param drive The desired drive mode.
   * @return A string indicating the name of the drive mode switch.
   */
  static std::string SwitchDrive(int drive);

  /**
   * Toggles the drive mode of the robot.
   *
   * @return The new drive mode as a string.
   */
  std::string toggleDrive();

  // The current drive train mode, between curvature, arcade, and tank.
  static int driveNum;
  /**
   * @brief Initializes the Drivetrain object.
   *
   * This constructor is responsible for initializing the Drivetrain object and
   * setting default values.
   */
  Drivetrain();

 private:
  /**
   * @brief Drives the robot using arcade drive.
   *
   * Arcade drive uses the left joystick for forward and backward movement, and
   * the right joystick for left and right movement.
   */
  void ArcadeDrive();

  /**
   * @brief Drives the robot using curvature drive.
   *
   * Curvature drive applies curvature to turns and a negative inertia
   * accumulator.
   */
  void CurvatureDrive();

  /**
   * @brief Drives the robot using tank drive.
   *
   * Tank drive uses the left and right joysticks for controlling the left and
   * right sides of the robot.
   */
  void TankDrive();
};
}  // namespace Robot