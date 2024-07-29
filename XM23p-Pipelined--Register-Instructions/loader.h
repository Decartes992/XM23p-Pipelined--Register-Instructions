#ifndef LOADER_H
#define LOADER_H
#include <stdint.h> // Include stdint.h to use uint8_t and uint16_t

// Define memory sizes and other constants
#define IMEM_SIZE 65536
#define DMEM_SIZE 65536
#define REGFILE_SIZE 8
#define ARG_COUNT 2
#define HEX_BASE 16
#define ASCII_PRINTABLE_START 32
#define ASCII_PRINTABLE_END 126
#define HEADER_START 8
#define BYTE_SIZE 2
#define ASCII_SIZE 4
#define IMEM_SHIFT 1
#define DMEM_SHIFT 1
#define BYTE_MASK 0xFF
#define ADDRESS_SHIFT 1
#define DATA_SHIFT 8
#define LINE_SIZE 100
#define READ 0x1
#define WRITE 0x2 // RECHECK
#define DEBUGGER_MODE 1
#define EXECUTION_MODE 0





// PSW structure
typedef struct {
    unsigned char ZF; // Zero Flag
    unsigned char SF; // Sign Flag
    unsigned char OF; // Overflow Flag
    unsigned char CF; // Carry Flag
    unsigned char slp; // SLP Flag
} PSW;

// Declare memory arrays
extern unsigned short IMEM[IMEM_SIZE / 2];
extern unsigned short DMEM[DMEM_SIZE / 2];
extern unsigned short reg_file[REGFILE_SIZE];
extern unsigned short IMAR;
extern unsigned short ICTRL;
extern unsigned short IR; // Instruction Register
extern unsigned long clock_ticks; // Global variable to store clock ticks
extern unsigned short breakpoint;
extern PSW psw; // Processor Status Word
extern unsigned short start_address; // Start address set by S9 record

// Declare new variables for memory access
extern unsigned short DMAR; // Data Memory Address Register
extern unsigned char DCTRL; // Data Control Register
extern unsigned short DMBR; // Data Memory Buffer Register

// Declare variables for instruction fields
extern unsigned char rc;
extern unsigned char wb;
extern unsigned char src;
extern unsigned char dst;
extern unsigned char con;
extern unsigned char bb;
extern unsigned char prpo;
extern unsigned char dec;
extern unsigned char inc;
extern unsigned char v;
extern unsigned char c;
extern unsigned char n;
extern unsigned char z;
extern unsigned char slp;

// Declare functions for loading S-Records and displaying memory
void loadSRecord(const char* filename);
void displayMemory(unsigned char* memory, int start, int end);
void manager(int argc, char* argv[]);
unsigned int calculateChecksum(const char* line, int count, int dataLength);


uint8_t memory_read_byte(uint16_t address);
uint16_t memory_read_word(uint16_t address);
void memory_write_byte(uint16_t address, uint8_t value);
void memory_write_word(uint16_t address, uint16_t value);

#endif // LOADER_H
