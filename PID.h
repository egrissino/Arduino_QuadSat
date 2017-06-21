// Evan Grissino
// 04/06/2016
// PID object class

class PID {
    private:
        int P, I, D;
        int Integrator, Derivator;
        int Integrator_max, Integrator_min;
        double P_val, I_val, D_val, dt;
        double start, old_time;
    
    public:
        double set_point, error, PID_const;
    
    //PID();
    PID(double set, double init);
    
    double update(double current, double time);
    double update(double current);
    
    void set_P (double p_val);
    void set_I (double i_val);
    void set_D (double d_val);
    void set (double set);
    void setPIDK (double p_val, double i_val, double d_val, double gain);
    void set_limits(double low, double high);
    void set_gain(double gain);
    void begin(int time);
};