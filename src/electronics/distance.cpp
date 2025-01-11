#include "globals.h"
#include "pros/misc.h"
#include "electronic/distance.h"

using namespace Robot;
using namespace Robot::Globals;


DistanceSensor::DistanceSensor() { ; }

int DistanceSensor::get_distance() {
    return distance_sensor.get();
}