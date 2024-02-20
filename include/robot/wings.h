#pragma once


namespace Robot {
/**
 * @brief The Wings class represents the wings of a robot.
 *
 * The Wings class provides functionality to control and operate the wings of a robot.
 * It allows the robot to perform various actions related to the wings, such as running them.
 */
class Wings {
public:
    /**
     * @brief Runs the wings.
     *
     * This function activates the wings and starts their operation.
     * It allows the robot to perform actions that involve the movement or control of the wings.
     *
     * @note Make sure to initialize the wings before calling this function.
     */

    void run();

    /**
     * @brief Sets the state of the wings.
     * @param wingState The state of the wings.
     */
    void setState(bool wingState);

    /**
     * @brief Gets the current state of the wings.
     * @return The current state of the wings.
     */
    bool getState();

private:
    /** The current state of the wings. 
     *  The state variable represents the current state of the wings.
     *  It can be either true or false, indicating whether the wings are activated or deactivated.
     *  This variable is used to control the behavior of the wings and to query their current state.
     */
    bool state; 
};

}