#pragma once
#include "pros/apix.h" // IWYU pragma: export
#include "robot/auton.h"

namespace Robot
{

/**
 * @brief The selector screen allows for choosing modes that the drivetrain and
 * autonomous take.
 */
class selector_screen {
public:
	/**
	 * @brief Constructor.
	 */

	selector_screen();

	/**
	 * @brief Function to create and initialize the selector screen.
	 *
	 * This function creates a tab view object and adds two tabs to it:
	 * "Autonomous select" and "Drive select". It also adds event callbacks to the
	 * tabs for updating the UI. The function creates labels, switches, and a
	 * dropdown list for selecting alliance color, skills, and autonomous mode. It
	 * also creates a label and a roller for selecting the current drive mode.
	 */
	void selector();

	/**
	 * @brief Returns the alliance color selected.
	 * 0 = Blue, 1 = Red, -1 = Skills.
	 */
	short get_auton_type();

private:
	/**
	 * @brief Value of the last selected competition autonomous when switching to
	 * a skills autonomous.
	 */
	static Autonomous::AUTON_ROUTINE lastAuton;

	static lv_color_t lastColor;

	constexpr static char redAutons[] = "Red Left\nRed Right";

	constexpr static char blueAutons[] = "Blue Left\nBlue Right";

	constexpr static char driveModes[] = "Curvature Drive\nArcade Drive\nTank Drive";

	static void auton_ui_update(lv_event_t *e);
};
} // namespace Robot