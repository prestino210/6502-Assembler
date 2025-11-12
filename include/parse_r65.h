#ifndef PARSE_ASM_H
#define PARSE_ASM_H
#include <stdint.h>
#include "tokenize_asm.h"

typedef struct {
    int opcode;
    int bytes;
} Opcode_info;

typedef struct {
    uint16_t offset;
    char* label;
} Label;


uint8_t* parse_r65(Statement* statements); // seperate statements by ';',
                                       // get opcode for each statement, add to a buffer of bytes, then return buffer
Opcode_info get_opcode(Statement statement, uint16_t offset); // run switch statement for instruction, 
                                     // use operands to decide variation, 
                                     // and return completed opcode (check validity in all steps)

#endif
