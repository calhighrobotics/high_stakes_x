#pragma once

namespace Robot {

        
    class Puncher {
        public:
            /**
            * @brief Runs the puncher based on the given autonomous value.
            *
            * This function executes the puncher mechanism based on the provided autonomous value.
            * It contains conditionals that determine the behavior of the puncher.
            *
            * @param autonVal The autonomous value to determine the puncher behavior.
            */
            void run(int autonVal);

            /**
            * @brief Sets the distancePuncher variable based on the punch parameter.
            *
            * This function sets the distancePuncher variable based on the provided punch parameter.
            * The distancePuncher variable determines the behavior of the puncher mechanism.
            *
            * @param punch The value to set the distancePuncher variable to.
            */
            void setDistancePuncher(bool punch);
            
            /**
            * @brief Toggles whether the distance sensor is activated or not and prints it out.
            *
            * This function toggles the distance sensor activation by flipping the value of the distancePuncher variable.
            * It then prints out the current state of the distancePuncher variable.
            */
            void PuncherSwitch();

        private:
            /**
            * @brief Checks if the distance sensor is connected and whether to shoot.
            *
            * This function checks if the distance sensor is connected and retrieves the distance from the triball.
            * It uses the distance to determine whether to shoot or not.
            *
            * @return The value returned of whether to shoot or no.
            */
            int toShoot();
            
            /**
            * @brief Determines whether to use the distance sensor or not.
            *
            * The distancePuncher variable decides whether to use the distance sensor or not.
            * If distancePuncher is true, the distance sensor is used. If it is false, the distance sensor is not used.
            */
            bool distancePuncher;
        };
}