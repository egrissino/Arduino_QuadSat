// Evan Grissino
// 04/06/2016
// PID object class

#include "PID.h"


PID::PID(double set, double init) {
    P = 2;
    I = 1;
    D = 0;

    Derivator = 0;
    Integrator = 0;
    Integrator_max = 100;
    Integrator_min = -100;
    PID_const = 1;
    
    P_val = 0;
    I_val = 0;
    D_val = 0;

    set_point = set;
    error = init - set;
};

void PID::begin(int time) {
    start = time;       // start time in millisecond
    old_time = start;
}

void PID::set_limits(double low, double high) {
    Integrator_max = high;
    Integrator_min = low;
}

void PID::set_gain(double gain) {
    PID_const = gain;
}

void PID::set_P(double p_val) {
    P = p_val;
};

void PID::set_I(double i_val) {
    I = i_val;
};

void PID::set_D(double d_val) {
    D = d_val;
};

void PID::set(double set) {
    set_point = set;
    Integrator = 0;
    Derivator = 0;
    begin(old_time);
};

void PID::setPIDK (double p_val, double i_val, double d_val, double gain) {
    set_P( p_val );
    set_I( i_val );
    set_D( d_val );
    set_gain( gain );
}

double PID::update(double current) {
    double old_error = error;
    error = set_point - current;
    
    Integrator += error ;
    Derivator = (error - old_error);
    
    P_val = P * error;
    I_val = I * Integrator;
    D_val = D * Derivator;
    
    return (P_val + I_val + D_val) * PID_const;
};

double PID::update(double current, double time) {
    dt = time - old_time;
    old_time = time;
    
    double old_error = error;
    error = set_point - current;
    
    Integrator += error * dt / 1000 ;
    Derivator = (error - old_error) / dt / 1000;
    
    P_val = P * error;
    I_val = I * Integrator;
    D_val = D * Derivator;
    
    return (P_val + I_val + D_val) * PID_const;
};
