// Header guard - Ensures that the header file will not get double imported.
#pragma once

/**
 * @file drivetrain.h
 * @brief Contains the declaration of the Drivetrain class.
 */

namespace Robot {

    /**
     * @class Drivetrain
     * @brief Represents the drivetrain of the robot.
     * 
     * The Drivetrain class is responsible for controlling the movement of the robot's drivetrain.
     * It provides functions to interpret joystick inputs and convert them into appropriate drivetrain movements.
     * The drivetrain can be controlled using different drive modes, such as tank drive or arcade drive.
     * 
     * The Drivetrain class also allows setting and retrieving the deadzone value for the joystick.
     * The deadzone is a range around the joystick's resting position where no movement is registered.
     * By adjusting the deadzone value, the sensitivity of the joystick inputs can be fine-tuned.
     */
    class Drivetrain {
    public:
        void run();

        /**
         * @brief Sets the joystick deadzone.
         * 
         * @param newDeadZone The new deadzone value.
         * 
         * The deadzone is a range around the joystick's resting position where no movement is registered.
         * This function allows you to set the deadzone value to filter out small joystick movements.
         * 
         * @details The deadzone value determines the sensitivity of the joystick inputs.
         * A higher deadzone value will require larger joystick movements to register any movement in the drivetrain.
         * Conversely, a lower deadzone value will make the drivetrain more responsive to small joystick movements.
         */
        void setdeadzone(int newDeadZone);

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
        void SwitchDrive();
        int driveMode;
        void Drivetrain();
    private:
        /**
         * @brief Drives the robot using arcade drive.
         * 
         * Arcade drive uses the left joystick for forward and backward movement, and the right joystick for left and right movement.
         */
        void ArcadeDrive();

        /**
         * @brief Drives the robot using tank drive.
         * 
         * Tank drive uses the left and right joysticks for controlling the left and right sides of the robot.
         */
        void TankDrive();

        /**
         * @brief Checks if the controller input is inside the deadzone range.
         * 
         * @param entry The controller input to check.
         * @return The input value if it is outside the deadzone range, otherwise 0.
         */
        int CheckDeadzone(int entry);

        int deadzone; ///< The deadzone value for the joystick.
    };
}