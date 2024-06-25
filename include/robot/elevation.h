#pragma once


namespace Robot {

/**
 * @brief The Elevation class represents the elevation control of a robot.
 * 
 * This class provides functionality to control the elevation of a robot.
 * It contains a run() method to initiate the elevation control process.
 * The state variable represents the current state of the elevation control.
 */
class Elevation {
public:

    /**
     * @brief Run the elevation control process.
     * 
     * This method initiates the elevation control process.
     */
    void run();

private:
    
    bool state; /**< The current state of the elevation control. */
};

}