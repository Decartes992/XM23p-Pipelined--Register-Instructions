/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: instructions.c
File Purpose: This file contains the functions to handle execution of specific instructions for the XM23P emulator.
*/
// instructions.c

#include "loader.h"
#include "instructions.h"

void updatePSW_ZF(unsigned short result) {
    psw.ZF = (result == 0);
}

void updatePSW_SF(unsigned short result) {
    psw.SF = ((result & 0x8000) != 0);
}

void updatePSW_OF(unsigned short a, unsigned short b, unsigned short result) {
    psw.OF = (((a ^ b ^ result ^ (result >> 1)) & 0x8000) != 0);
}

void updatePSW_CF(unsigned int result) {
    psw.CF = (result > 0xFFFF);
}

void executeADD(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] + operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF((unsigned int)reg_file[dst] + operand);
    reg_file[dst] = result;
}

void executeSUB(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] - operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF((unsigned int)reg_file[dst] - operand);
    reg_file[dst] = result;
}

void executeAND(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] & operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    reg_file[dst] = result;
}

void executeOR(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] | operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    reg_file[dst] = result;
}

void executeADDC(unsigned char dst, unsigned short operand) {
    unsigned int result = reg_file[dst] + operand + psw.CF;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF(result);
    reg_file[dst] = (unsigned short)result;
}

void executeSUBC(unsigned char dst, unsigned short operand) {
    unsigned int result = reg_file[dst] - operand - psw.CF;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF(result);
    reg_file[dst] = (unsigned short)result;
}

void executeDADD(unsigned char dst, unsigned short operand) {
    unsigned int result = reg_file[dst] + operand + psw.CF;
    updatePSW_ZF(result);
    updatePSW_CF(result);
    reg_file[dst] = (unsigned short)result;
}

void executeCMP(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] - operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF((unsigned int)reg_file[dst] - operand);
}

void executeXOR(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] ^ operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    reg_file[dst] = result;
}

void executeBIT(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] & operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
}

void executeBIC(unsigned char dst, unsigned short operand) {
    reg_file[dst] &= ~operand;
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeBIS(unsigned char dst, unsigned short operand) {
    reg_file[dst] |= operand;
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeMOV(unsigned char dst, unsigned short operand) {
    reg_file[dst] = operand;
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeSWPB(unsigned char dst) {
    unsigned short value = reg_file[dst];
    reg_file[dst] = (value << 8) | (value >> 8);
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeSRA(unsigned char dst) {
    unsigned short value = reg_file[dst];
    reg_file[dst] = (value >> 1) | (value & 0x8000);
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeRRC(unsigned char dst) {
    unsigned short value = reg_file[dst];
    unsigned short newCarry = value & 0x0001;
    reg_file[dst] = (value >> 1) | (psw.CF << 15);
    psw.CF = newCarry;
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeSWAP(unsigned char src, unsigned char dst) {
    unsigned short value = reg_file[dst];
    reg_file[dst] = reg_file[src];
    reg_file[src] = value;
}

void executeSXT(unsigned char dst) {
    reg_file[dst] = (reg_file[dst] & 0xFF) | ((reg_file[dst] & 0x80) ? 0xFF00 : 0x0000);
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeMOVLZ(unsigned short dst, unsigned short operand) {
    reg_file[dst] = operand & 0x00FF;
}

void executeMOVL(unsigned char dst, unsigned short operand) {
    reg_file[dst] = (reg_file[dst] & 0xFF00) | (operand & 0x00FF);
}

void executeMOVLS(unsigned char dst, unsigned short operand) {
    reg_file[dst] = 0xFF00 | (operand & 0x00FF);
}

void executeMOVH(unsigned char dst, unsigned short operand) {
    reg_file[dst] = (operand << 8) | (reg_file[dst] & 0x00FF);
}

void executeSETCC() {
    if (c) psw.CF = 1;
    if (v) psw.OF = 1;
    if (n) psw.SF = 1;
    if (z) psw.ZF = 1;
    if (slp) psw.slp = 1;
}

void executeCLRCC() {
    if (c) psw.CF = 0;
    if (v) psw.OF = 0;
    if (n) psw.SF = 0;
    if (z) psw.ZF = 0;
    if (slp) psw.slp = 0;
}


void execute_ld(unsigned char src, unsigned char dst) {
    DMAR = reg_file[src] / 2;
    DCTRL = READ;

    if (!wb) {
        // Read byte
        reg_file[dst] = memory_read_byte(DMAR);
    }
    else {
        // Read word
        reg_file[dst] = memory_read_word(DMAR);
    }
}

void execute_ldr(unsigned char src, unsigned char dst, char offset) {
    DMAR = (reg_file[src] + offset) / 2;
    DCTRL = READ;

    if (!wb) {
        // Read byte
        reg_file[dst] = memory_read_byte(DMAR);
    }
    else {
        // Read word
        reg_file[dst] = memory_read_word(DMAR);
    }
}

void execute_st(unsigned char src, unsigned char dst) {
    DMAR = reg_file[dst] / 2;
    DCTRL = WRITE;
    DMBR = reg_file[src];
    
    if (!wb) {
        // Write byte
        memory_write_byte(DMAR, DMBR & 0xFF);
    } else {
        // Write word
        memory_write_word(DMAR, DMBR);
    }
}

void execute_str(unsigned char src, unsigned char dst, char offset) {
    DMAR = (reg_file[src] + offset) / 2;
    DCTRL = WRITE;
    DMBR = reg_file[src];
    
    if (!wb) {
        // Write byte
        memory_write_byte(DMAR, DMBR & 0xFF);
    } else {
        // Write word
        memory_write_word(DMAR, DMBR);
    }
}


// Function to write a byte to memory
void memory_write_byte(uint16_t address, uint8_t value) {
    DMEM[address] = value;
}

// Function to write a word to memory
void memory_write_word(uint16_t address, uint16_t value) {
    DMEM[address] = (value >> 8) & 0xFF;
    DMEM[address + 1] = value & 0xFF;
}


// Function to read a byte from memory
uint8_t memory_read_byte(uint16_t address) {
    return DMEM[address];
}

// Function to read a word from memory
uint16_t memory_read_word(uint16_t address) {
    return (DMEM[address] << 8) | DMEM[address + 1];
}
