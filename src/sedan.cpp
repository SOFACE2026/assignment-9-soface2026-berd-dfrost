#include "sedan.hpp"
#include <array>

static const std::array<double, 7> gear_ratios = {-1, 1, 2, 3, 4, 5, 6};

Sedan::Sedan() : current_gear(0)
{
}

void Sedan::shift_up()
{
    // if there's room to shift up, we do, else silently fail
    if (this->get_current_gear_ratio() < gear_ratios.size()-1) this->current_gear++;
}

void Sedan::shift_down()
{
    // if there's room to shift down, we do, else silently fail
    if (this->get_current_gear_ratio() > 0) this->current_gear--;
}

double Sedan::get_torque(double engine_rpm, double throttle)
{
    // just returns 100 Nm times the throttle ratio
    // independent of engine_rpm
    return 1950 * throttle;
}

double Sedan::get_weight()
{
    // hardcoded value
    return 2000;
}

double Sedan::get_wheel_radius()
{
    // hardcoded value
    return 0.3;
}

double Sedan::get_current_gear_ratio()
{
    // just return the local variable of the object
    return gear_ratios[this->current_gear];
}