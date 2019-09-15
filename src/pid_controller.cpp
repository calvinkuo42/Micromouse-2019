#include "pid_controller.h"
#include "pins.h"
#include "globals.h"
#include "read_ir.h"

PIDController::PIDController() {
    this->reset();
}

/***
 * Assignment 3
 * 
 * Implement PID!
 ***/

void PIDController::reset() volatile {    
    /**
     * You'll have a lot to keep track of. Make sure to reset all 
     * those variables here.
     **/

    m_goalW = 0;
    m_goalX = 0;
    m_countsW = 0;
    m_countsX = 0;

    m_pwmW = 0;
    m_pwmX = 0;

    m_errorW = 0;
    m_errorX = 0;
    m_errorW_old = 0;
    m_errorX_old = 0;
}

void PIDController::update() volatile {
    /**
     * Update your PID controller. This is what should be called
     * every systick, so you should call all your important
     * functions here.
     **/
     getSensorFeedback();
     //get_ir_error();
     x_controller();
     w_controller();
     updateMotorPwm();
}

void PIDController::setXGoal(int counts) {
    /**
     * Set goal for X controller.
     **/
     m_goalX = counts;
}

void PIDController::setWGoal(int counts) {
    /**
     * Set goal for W controller. Make sure to associate a turning
     * direction with a sign, e.g., positive is clockwise, negative
     * is counter-clockwise.
     **/
     m_goalW = counts;
}

void PIDController::setWCounts(int counts) {
    m_countsW = counts;
}

bool PIDController::isDone() volatile {
    /**
     * When is the PID done? Well, probably when you've reached
     * your goals...
     **/
     if (m_errorW == 0 && m_errorX == 0)
        return true;
    return false;
}

char* PIDController::getData() {
    /**
     * Use this function to print data about your PID,
     * because you can't print directly in systick!
     **/
    sprintf(buf, "goalx: %d\tgoalw: %d\tpwmx: %.3f\tpwmw: %.3f\terrorx: %d\terrorw: %d\n",
        m_goalX,
        m_goalW,
        m_pwmX,
        m_pwmW,
        m_errorX,
        m_errorW);
    return buf;
}
int PIDController::returnErrorW() {
    return m_errorW;    
}
int PIDController::returnErrorX() {
    return m_errorX;
}



/**
 * Private functions to do the internal work for PID.
 **/
void PIDController::getSensorFeedback() volatile {
    /**
     * Update sensor values, from encoders
     **/
     m_countsX = (encoders.getPulsesR() + encoders.getPulsesL())/2;
     m_countsW = encoders.getPulsesR() - encoders.getPulsesL();
}

float PIDController::get_ir_error() volatile {
    float error;

    /*
    - These MID values can be hardcoded, or maybe even calculated at some
    point in your program...
    - You may find that setting these mid values to something that doesn't
    quite correspond to the middle (e.g., MIDR slightly to the right of the
    middle rather that directly in the center), may make your Rat perform
    better. Play around with it!
    */  
    if (flash_ir(R_EMITTER, R_RECEIVER) > MIDR) {
        error = flash_ir(R_EMITTER, R_RECEIVER) - MIDR;
    }
    else if (flash_ir(L_EMITTER, L_RECEIVER) > MIDL) {
        // Make sure to change the sign for the error!
        error = MIDL - flash_ir(L_EMITTER, L_RECEIVER);
    }
    else {
        // No useful information from IR's
        error = 0;
    }

    return error;
}

void PIDController::x_controller() volatile {
    /**
     * Your X PID controller, sets m_pwmX
     **/
    m_errorX = m_goalX - m_countsX;
    m_pwmX = KpX * m_errorX + KdX * (m_errorX - m_errorX_old);
    m_errorX_old = m_errorX;
    if (isStraight) {
        if( m_pwmX > 0.2)
            m_pwmX = 0.2;
    }
    else
        m_pwmX = 0;
}

void PIDController::w_controller() volatile {
    /**
     * Your W PID controller, sets m_pwmW
     **/
     m_errorW = m_goalW - m_countsW;
     m_pwmW = KpW * m_errorW + KdW * (m_errorW - m_errorW_old); //+ get_ir_error() * IR_SCALING
     m_errorW_old = m_errorW;
}

void PIDController::updateMotorPwm() volatile {
    /**
     * Takes m_pwmX, m_pwmW, and adjusts the motors based on those values.
     **/
     motors.setRightPwm(m_pwmX + m_pwmW);
     motors.setLeftPwm(m_pwmX - m_pwmW);
}




