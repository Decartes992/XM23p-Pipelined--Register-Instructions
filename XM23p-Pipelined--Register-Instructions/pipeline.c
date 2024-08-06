#include <stdio.h>
#include "loader.h"
#include "pipeline.h"
#include "execute_instructions.h"

/*
void pipelineExecute(unsigned short* PC, int display) {
    InstructionType type;
    int instruction_count = 1;
    unsigned short IR_prev = 0;
    unsigned char rc, wb, src, dst, con, bb, v = psw.OF, c = psw.CF, slp = psw.slp, z = psw.ZF, n = psw.SF;
    IR = 0x6800;

    printf("Clock  PC   Instruction      Fetch      Decode      Execute    Z N V C\n");
    printf("--------------------------------------------------------------------------\n");

    while (!(IR == 0x0000 || *PC == breakpoint)) {
        F0Stage(PC);
        D0Stage(&type, &rc, &wb, &src, &dst, &con, &bb, display, PC, &v, &c, &slp, &n, &z);

        if (display) StatusPrint(PC, IR_prev);

        tick();

        IR_prev = IR;

        F1Stage();
        E0Stage(type, rc, wb, src, dst, con, bb, v, c, slp, n, z);

        if (type == LD || type == LDR || type == ST || type == STR) {
            E1Stage();  // Add the memory access completion stage
        }

        if (display) StatusPrint(PC, IR_prev);

        tick();
    }
    if (display) {
        if (*PC == breakpoint) {
            printf("Breakpoint reached at %04X. Execution stopped.\n\n", *PC);
        }
        else {
            printf("End of program reached. Execution stopped.\n\n");
        }
    }
    return;
}
*/
// pipeline.c

#include <stdio.h>
#include "loader.h"
#include "pipeline.h"
#include "execute_instructions.h"

void pipelineExecute(unsigned short* PC, int display) {
    InstructionType type;
    int instruction_count = 1;
    unsigned short IR_prev = 0;
    IR = 0x6800;

    printf("Clock  PC   Instruction      Fetch      Decode      Execute    Z N V C\n");
    printf("--------------------------------------------------------------------------\n");

    while (!(IR == 0x0000 || *PC == breakpoint)) {
        F0Stage(PC);
        D0Stage(&type);

        if (display) StatusPrint(PC, IR_prev);

        tick();

        IR_prev = IR;

        F1Stage();
        E0Stage(type);

        if (type == LD || type == LDR || type == ST || type == STR) {
            E1Stage();  // Add the memory access completion stage
        }

        if (display) StatusPrint(PC, IR_prev);
        displayRegisters();
        tick();
    }
    if (display) {
        if (*PC == breakpoint) {
            printf("Breakpoint reached at %04X. Execution stopped.\n\n", *PC);
        }
        else {
            printf("End of program reached. Execution stopped.\n\n");
        }
    }
    return;
}

void D0Stage(InstructionType* type) {
    *type = getInstructionType(IR);
    extractFields(IR, *type);
}

void E0Stage(InstructionType type) {
    if (type != INVALID) {
        unsigned short operand = getOperand(rc, src);
        executeInstruction(type, operand);
    }
}

void F0Stage(unsigned short* PC) {
    IMAR = *PC/2;
    ICTRL = READ;
    *PC += 2;
}

void F1Stage() {
    IR = IMEM[IMAR];
}

void E1Stage() {
    if (DCTRL == READ) {
        DMBR = memory_read_byte(DMAR);
    }
    else if (DCTRL == WRITE) {
        memory_write_byte(DMAR, DMBR);
    }
}


void tick() {
    clock_ticks++;
}

void StatusPrint(unsigned short* PC, unsigned short IR_prev) {
    if (clock_ticks % 2 == 0)
        printf("  %-3d %-9X %-10X F0: %-7X D0: %-5X \n", clock_ticks, IMAR, IMEM[IMAR / 2], IMAR, IR);
    else
        printf("  %-24d F1: %-19X E0: %-7X %d %d %d %d\n", clock_ticks, IR, IR_prev, psw.ZF, psw.SF, psw.OF, psw.CF);
}
