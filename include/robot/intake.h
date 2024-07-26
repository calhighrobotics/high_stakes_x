#pragma once
#include <stdint.h>

namespace Robot {

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
   * @brief Runs intake for a certain interval of time.
   */
  void interval(const uint32_t time);

  /**
   * @brief Toggles intake elevation.
   */
  void toggle();

 private:
  bool elevated;
};
}  // namespace Robot