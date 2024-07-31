#pragma once

namespace Robot
{

/**
 * @brief The Intake class represents a robot intake system.
 */
class Intake {
public:
	/**
	 * @brief Runs the main function of the intake system.
	 *
	 * Takes optional user input to control the direction of the intake system in
	 * autonomous.
	 */
	void run();

	/**
	 * @brief Outakes rings and scores them inside of latched mobile goal.
	 */
	void score();

	Intake();

	/**
	 * @brief Toggles intake elevation.
	 */
	void toggle();

private:
	bool elevated;

	/**
	 * @brief blue is false, red is true.
	 */
	bool alliance_color;

	/**
	 * @brief Runs intake in async.
	 *
	 * automatic scoring and ejection of rings using color sensor.
	 */
	void async();

	/**
	 @brief Ejects an enemy color ring.
	 */
	void eject();
};
}