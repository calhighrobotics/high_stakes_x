// Header guard - Ensures that the header file will not get double imported.
#pragma once

namespace Robot {

    /**
         * @file drivetrain.h
         * @brief Contains the declaration of the Drivetrain class.
         */

        /**
         * @class Drivetrain
         * @brief Represents the drivetrain of a robot.
         * 
         * The Drivetrain class is responsible for controlling the movement of the robot's drivetrain.
         * It provides functions to run the drivetrain and set the joystick deadzone.
         */
        class Drivetrain {
        public:
            /**
             * @brief Runs the drivetrain.
             * 
             * This function is responsible for controlling the movement of the robot's drivetrain.
             * It executes the necessary actions to make the robot move according to the current drive mode.
             * 
             * @details The drivetrain can be controlled using different drive modes, such as tank drive or arcade drive.
             * This function implements the logic to interpret the joystick inputs and convert them into appropriate drivetrain movements.
             */
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

        /**
         * @brief Switches the drive mode.
         * This function is responsible for switching the drive mode of the robot.
         * The drive mode determines how the robot responds to joystick inputs.
         * It can be used to switch between different control schemes or driving behaviors.
         */
        void SwitchDrive();
    };

        /**
         * @brief Constructs a new Drivetrain object.
         */
        Drivetrain();

    private:
        /**
         * @brief Drives the robot using arcade drive.
         * @details Uses the left joystick for forward and backward movement, and the right joystick for left and right movement.
         */
        void ArcadeDrive();

        /**
         * @brief Drives the robot using tank drive.
         * @details Uses the left and right joysticks for controlling the left and right sides of the robot.
         */
        void TankDrive();

        /**
         * @brief Checks if the controller input is inside the deadzone range.
         * @param entry The controller input to check.
         * @return The input value if it is outside the deadzone range, otherwise 0.
         */
        int CheckDeadzone(int entry);

        int deadzone; ///< The deadzone value for the joystick.
    };
}