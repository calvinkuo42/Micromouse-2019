#include "assignment2.h"
#include "globals.h"


void read_encoders() {
    while (true) {
        encoders.printValues();
        wait(0.5);
    }
}

void basic_motor_movement() {
    motors.setRightPwm(0.2);
    motors.setLeftPwm(0.2);
    
    wait(3);

    motors.setRightPwm(-0.2);
    motors.setLeftPwm(-0.2);

    wait(3);

    motors.setRightPwm(0.2);
    motors.setLeftPwm(-0.2);
}

void motor_test() {
    motors.setRightPwm(0.2);
    motors.setLeftPwm(0.2);    
}


