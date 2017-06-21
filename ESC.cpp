// Evan Grissino
// 06/21/2017
// ESC handler objects

#include "ESC.h"

QuadESC::QuadESC( void ) {
    throttleChangeDelay = 50;       // milliseconds
    minPulseRate = 1000;
    maxPulseRate = 1000;
}

QuadESC::QuadESC( int minPulse = 1000, int maxPulse = 1000 ) {
    throttleChangeDelay = 50;       // milliseconds
}

void QuadESC::initalize( void ) {
    // Attach the ESC's
    FR.attach(FRONT_RIGHT, minPulseRate, maxPulseRate);
    FL.attach(FRONT_LEFT, minPulseRate, maxPulseRate);
    BR.attach(BACK_RIGHT, minPulseRate, maxPulseRate);
    BL.attach(BACK_LEFT, minPulseRate, maxPulseRate);
    
    //Initalize motors with 0 value
    writeToEscs(0);
}

int QuadESC::normalizeThrottle(int value) {
    if(value < 0) {
        return 0;
    } else if(value > MAX_THROTTLE) {
        return MAX_THROTTLE;
    }

    return value;
}

void QuadESC::startUpMotors( void ){
    incrimentThrottleAll(30);
    incrimentThrottleAll(-30);
}

void QuadESC::update( double yaw, double pitch, double roll, int throt) {
    
    throttle = normalizeThrottle( throt );
    
    double thrusts[4] = {throttle, throttle, throttle, throttle};
    
    thrusts[0] += throttle * pitch;
    thrusts[1] += throttle * pitch;
    
    thrusts[2] += throttle * pitch;
    thrusts[2] += throttle * pitch;
    
    thrusts[0] -= throttle * roll;
    thrusts[1] += throttle * roll;
    
    thrusts[2] -= throttle * roll;
    thrusts[3] += throttle * roll;
    
//    thrusts[0] -= throttle * yaw;
//    thrusts[1] += throttle * yaw;
//    
//    thrusts[2] -= throttle * yaw;
//    thrusts[3] += throttle * yaw;
    
    for (int i = 0; i < 4; i++) {
        ESCs[i]->write(thrusts[i]);
    }
    
}


void QuadESC::changeThrottle( Servo* esc, int throttle ) {
    esc->write(throttle);
}

void QuadESC::incrimentThrottleAll(int throttle) {
    
    int currentThrottle = FR.read();

    throttle += currentThrottle;

    int step = 1;
    if(throttle < currentThrottle) {
        step = -1;
    }

    // Slowly move to the new throttle value 
    while(currentThrottle != throttle) {
        writeToEscs(currentThrottle + step);

        currentThrottle = FR.read();
        delay(throttleChangeDelay);
    }
}

void QuadESC::writeToEscs(int throttle) {
    for (int i = 0; i < 4; i++) {
        ESCs[i]->write( throttle );
    }
}