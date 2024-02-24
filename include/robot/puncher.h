#pragma once

namespace Robot {

    /**
    * @brief Represents a Puncher mechanism for a robot.
    *
    * @details The Puncher class provides functionality to control a puncher mechanism on a robot.
    * It allows running the puncher based on an autonomous value, setting the distancePuncher variable,
    * toggling the distance sensor activation, and checking whether to shoot or not.
    */
    class Puncher {
        public:
            /**
            * @brief Runs the puncher based on the given autonomous value.
            *
            * This function executes the puncher mechanism based on the provided autonomous value.
            * It contains conditionals that determine the behavior of the puncher.
            *
            * @note Make sure to have the Puncher object initialized before calling this function.
            *
            * @param autonVal The autonomous value to determine the puncher behavior.
            */
            void UserRun();

            void DistanceRun();

            /**
            * @brief Sets the distancePuncher variable based on the punch parameter.
            *
            * This function sets the distancePuncher variable based on the provided punch parameter.
            * The distancePuncher variable determines the behavior of the puncher mechanism.
            *
            * @param punch The value to set the distancePuncher variable to.
            */
            void setDistancePuncher(int punch);
            
            /**
            * @brief Toggles whether the distance sensor is activated or not and prints it out.
            *
            * This function toggles the distance sensor activation by flipping the value of the distancePuncher variable.
            * It then prints out the current state of the distancePuncher variable.
            */
            void PuncherSwitch();

            void run();




        private:
            /**
            * @brief Checks if the distance sensor is connected and whether to shoot.
            *
            * This function checks if the distance sensor is connected and retrieves the distance from the triball.
            * It uses the distance to determine whether to shoot or not.
            *
            * @return The value returned of whether to shoot or not.
            */
            int toShoot();
            
            /**
            * @brief Determines whether to use the distance sensor or not.
            *
            * The distancePuncher variable decides whether to use the distance sensor or not.
            * If distancePuncher is true, the distance sensor is used. If it is false, the distance sensor is not used.
            */
            int distancePuncherBool;
        };
}