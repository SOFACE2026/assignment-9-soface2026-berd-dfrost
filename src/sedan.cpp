#include "sedan.hpp"
#include <array>

static const std::array<double, 7> gear_ratios = {-1, 1, 2, 3, 4, 5, 6};

// Car starts in gear -1 for some reason
Sedan::Sedan() : current_gear(0) {}

// Shifts gear up
void Sedan::shift_up()
{
    // if there's room to shift up, we do, else silently fail
    if (this->get_current_gear_ratio() < gear_ratios.size()-1) this->current_gear++;
}

// Shifts gear down
void Sedan::shift_down()
{
    // if there's room to shift down, we do, else silently fail
    if (this->get_current_gear_ratio() > 0) this->current_gear--;
}

double Sedan::get_torque(double engine_rpm, double throttle)
{
    /* We approximated the needed constant torque of the engine by making a series for the velocity of the car where 
    
        v(torque)_{step+1} = v{step} + step*torque/(600kg*m*r), where v_0 = step*torque/(600kg*m*r)     (Derived by looking at the functions).

    When step = 0.01s and we want a duration of 10s that is 1000*steps = 10s, we obtain v_{1000} = v{0} + 1999*0.01*torque/(600kg*m)
    setting this to 32 m/s we obtain:
    
        1000*0.01*torque/(600kg*m*r) = 32 m/s => torque = 32*m/s*(600 kg*m*r)/10 = 1920 Nm.

    Using the derived constant torque we create a more realistic simulation of the torque, slowly increasing our torque when the
    engine rpm increases.
    */
    if(engine_rpm == 0){
        return 1000*throttle;
    }
    else if(engine_rpm < 2500){
        return 1920*throttle;
    }
    else{
        return 2067*throttle;
    } 
}

double Sedan::get_weight()
{
    // Respectable weight of 2000kg for the car 
    return 2000;
}

double Sedan::get_wheel_radius()
{
    // Wheel radius of 0.3m 
    return 0.3;
}

double Sedan::get_current_gear_ratio()
{
    // just return the local variable of the object
    return gear_ratios[this->current_gear];
}
