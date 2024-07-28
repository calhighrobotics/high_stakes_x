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

        enum Mode {
            CURVATURE_DRIVE, 
            ARCADE_DRIVE, 
            TANK_DRIVE
        };

        /**
         * @brief Returns the current deadzone value.
         * 
         * @return The deadzone value.
         * 
         * The deadzone is a range around the joystick's resting position where no movement is registered.
         * This function returns the current deadzone value that is being used by the drivetrain.
         * 
         * @details The deadzone value can be used to fine-tune the drivetrain's responsiveness to joystick inputs.
         * By retrieving the current deadzone value, you can adjust other parts of your code to take it into account.
         */
        int getdeadzone();


        /**
         * @brief Switches the DriveTrain mode between arcade and tank drive.
         * 
         * The drive mode determines how the drivetrain interprets the joystick inputs.
         * Arcade drive uses the left joystick for forward and backward movement, and the right joystick for left and right movement.
         * Tank drive uses the left and right joysticks for controlling the left and right sides of the robot.
         */
        static void SwitchDrive(int driveNum);


        Mode driveMode; ///< The current drive train mode

        /**
         * @brief Initializes the Drivetrain object.
         * 
         * This constructor is responsible for initializing the Drivetrain object and setting default values.
         */
        Drivetrain();

        std::string toggleDrive();

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