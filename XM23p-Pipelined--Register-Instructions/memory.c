/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: memory.c
File Purpose: This file contains the memory arrays and a function to display a range of memory.
*/
#include <stdio.h>
#include "loader.h"



// Function to read a byte from memory
uint8_t memory_read_byte(uint16_t address) {
    return DMEM[address];
}

// Function to read a word from memory
uint16_t memory_read_word(uint16_t address) {
    return (DMEM[address] << 8) | DMEM[address + 1];
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


// Function to display a range of memory
void displayMemory(unsigned char* memory, int start, int end) {
    // Loop from the start to the end of the memory range
    for (int i = start; i < end; i += HEX_BASE) {

        // Print the memory address
        printf("%04X: ", i);

        // Loop through each byte in the current memory word
        for (int j = 0; j < HEX_BASE; j++) {

            // If the current byte is within the memory range, print its value
            if (i + j < end) {
                printf("%02X ", memory[i + j]);
            }
            // Otherwise, print a placeholder
            else {
                printf("   ");
            }
        }

        printf(" ");

        // Loop through each byte in the current memory word again
        for (int j = 0; j < HEX_BASE; j++) {
            // If the current byte is within the memory range
            if (i + j < end) {
                unsigned char c = memory[i + j];
                // If the byte is a printable ASCII character, print it
                if (c >= ASCII_PRINTABLE_START && c <= ASCII_PRINTABLE_END) {
                    printf("%c", c);
                }
                // Otherwise, print a placeholder
                else {
                    printf(".");
                }
            }
            // If the current byte is outside the memory range, print a placeholder
            else {
                printf(" ");
            }
        }
        // Print a newline to separate memory words
        printf("\n");
    }
    // Print an extra newline for readability
    printf("\n");

    // Wait for the user to press enter before continuing
    getchar();
}

