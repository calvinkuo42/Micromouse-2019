#include <string>

#include "main_controller.h"
#include "pid_controller.h"
#include "globals.h"

MainController::MainController() {
    m_pid = new PIDController;
}

MainController::~MainController() {
    delete m_pid;
}

/***
 * Assignment 3
 * 
 * Implement PID! Most of this work is done in "pid_controller".
 ***/
void MainController::update() {
    // Update PID controller. This is the function you should be
    // calling every systick.
    m_pid->update();
}

/***
 * Assignment 3: Part 1
 * 
 * Get your mouse driving straight.
 ***/
void MainController::driveStraight() {
    /**
     * Set an X goal and W goal correctly! This is discussed in the lecture slides.
     * For help, see example code: pid/drive-straight.cpp
     **/
    isStraight = true;
    m_pid->setXGoal(1000000);
    m_pid->setWGoal(0);
    pc.printf("Driving straight\n");
}

/***
 * Assignment 3: Part 2
 * 
 * Get your mouse to turn, and drive a specific distance.
 ***/
void MainController::turn(int deg) {
    /**
     * For help, see example code: pid/turning.cpp
     **/
    isStraight = false;
    int factor;         
    if(deg > 0)          //left turn needs more
        factor = deg*4.7;
    else
        factor = deg*4.85;
    //factor = deg*5.3;
    m_pid->setWGoal(factor);
    m_pid->setXGoal(0);
    pc.printf("Turning %d degrees\n", deg);
    
    int stopCount = 0; // used to stop the seizurs, get rid of all the code in the loop beside the print if it doesn't work
    while(m_pid->returnErrorW() != 0) {
        if (m_pid->returnErrorW() < 5 || m_pid->returnErrorW() > -5)
            stopCount++;
        if (stopCount == 6)
            break;
        pc.printf(mainController.returndata());    
    }
    wait(0.75);
    m_pid->reset();
    encoders.reset();
}

void MainController::moveCells(float n) {
    /**
     * For help, see example code: pid/full.cpp
     **/
    isStraight = true;
    int factor = n*640;
    m_pid->setXGoal(factor);
    m_pid->setWGoal(0);
    pc.printf("Moving %d cells\n", n);
    while(m_pid->returnErrorX() != 0) {}
    wait(0.5);
    m_pid->reset();
    encoders.reset();
}

char* MainController::returndata() {
    return m_pid->getData();
}



