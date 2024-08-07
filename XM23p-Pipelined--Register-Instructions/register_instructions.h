#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

// Instruction function prototypes
void executeADD(unsigned char dst, unsigned short operand);
void executeADDC(unsigned char dst, unsigned short operand);
void executeSUB(unsigned char dst, unsigned short operand);
void executeSUBC(unsigned char dst, unsigned short operand);
void executeDADD(unsigned char dst, unsigned short operand);
void executeCMP(unsigned char dst, unsigned short operand);
void executeXOR(unsigned char dst, unsigned short operand);
void executeAND(unsigned char dst, unsigned short operand);
void executeOR(unsigned char dst, unsigned short operand);
void executeBIT(unsigned char dst, unsigned short operand);
void executeBIC(unsigned char dst, unsigned short operand);
void executeBIS(unsigned char dst, unsigned short operand);
void executeMOV(unsigned char dst, unsigned short operand);
void executeSWPB(unsigned char dst);
void executeSRA(unsigned char dst);
void executeRRC(unsigned char dst);
void executeSWAP(unsigned char src, unsigned char dst);
void executeSXT(unsigned char dst);
void executeMOVLZ(unsigned short dst, unsigned short operand);
void executeMOVL(unsigned char dst, unsigned short operand);
void executeMOVLS(unsigned char dst, unsigned short operand);
void executeMOVH(unsigned char dst, unsigned short operand);
void executeSETCC(unsigned char v, unsigned char c, unsigned char slp, unsigned char n, unsigned char z);
void executeCLRCC(unsigned char v, unsigned char c, unsigned char slp, unsigned char n, unsigned char z);



#endif // INSTRUCTIONS_H
