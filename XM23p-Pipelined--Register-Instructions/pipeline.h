// pipeline.h

#ifndef PIPELINE_H
#define PIPELINE_H

#include "decode_instructions.h"

// Function prototypes
void pipelineExecute(unsigned short* PC, int display);
void StatusPrint(unsigned short* PC, unsigned short IR_prev);
void F0Stage(unsigned short* PC);
void D0Stage(InstructionType* type);
void F1Stage();
void E0Stage(InstructionType type);
void E1Stage();
void tick();

#endif // PIPELINE_H
