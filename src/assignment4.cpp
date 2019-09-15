#include "assignment4.h"
#include "read_ir.h"
#include "pid_controller.h"
#include "pins.h"
#include "globals.h"

void left_ir_test() {
    while(true) {
        float ir = flash_ir(L_EMITTER, L_RECEIVER);
        pc.printf("left_ir %f\n", ir);
    }
}

void right_ir_test() {
    while(true) {
        float ir = flash_ir(R_EMITTER, R_RECEIVER);
        pc.printf("right_ir %f\n", ir);
    }
}

void mleft_ir_test() {
    while(true) {
        float ir = flash_ir(ML_EMITTER, ML_RECEIVER);
        pc.printf("mleft_ir %f\n", ir);
    }
}

void mright_ir_test() {
    while(true) {
        float ir = flash_ir(ML_EMITTER, ML_RECEIVER);
        pc.printf("mright_ir %f\n", ir);
    }
}

void all_ir_test() {
    while(true) {
        float irL = flash_ir(L_EMITTER, L_RECEIVER);
        pc.printf("left_ir %f\t", irL);
        
        float irR = flash_ir(R_EMITTER, R_RECEIVER);
        pc.printf("right_ir %f\t", irR);
        
        float irML = flash_ir(ML_EMITTER, ML_RECEIVER);
        pc.printf("mleft_ir %f\t", irML);
        
        float irMR = flash_ir(MR_EMITTER, MR_RECEIVER);
        pc.printf("mright_ir %f\t", irMR);
        printf("\n");
        wait(.5);
        
    }
}

void movement() {
    systick.start();
    
    //while (true)
    //      if (no wall in front and wall on side)
    //          move forward 1 cell /*later change to drive straight*/
    //      else if (wall in front and gap in side wall)
    //          turn towards direction with smaller sensor error
    //      else /*dead end*/
    //          turn around   
    
}