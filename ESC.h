// Evan Grissino
// 06/21/2017
// ESC handler objects

#include <Servo.h>
#include <arduino.h>

// Set these to the pin values where the ESC's are connected
#define FRONT_RIGHT 9
#define FRONT_LEFT  8
#define BACK_RIGHT  11
#define BACK_LEFT   10

// This represents the Servo angle that corresponds to 
// maximum throttle for your ESC/motor combination and must 
// be experimentally determined
#define MAX_THROTTLE 180

// Set this to 1 for clockwise rotors and 0 for counter-clockwise rotors
#define CLOCKWISE 1

class QuadESC {
    private:
    
    int minPulseRate;
    int maxPulseRate;
    int throttleChangeDelay;
    
    int throttle;
    int yaw, pitch, roll;
    
    public:
    
    Servo FR;
    Servo FL;
    Servo BR;
    Servo BL;
    
    Servo* ESCs[4] = {&FR, &FL, &BR, &BL};
    
    // Constuctors
    QuadESC( void );
    QuadESC( int minPulse, int maxPulse );
    
    // Public methods
    int normalizeThrottle(int value);
    
    void initalize( void );
    void startUpMotors( void );
    void changeThrottle( Servo* esc, int throttle );
    void incrimentThrottleAll(int throttle);
    void writeToEscs(int throttle);
    void update( double yaw, double pitch, double roll, int throt);
};