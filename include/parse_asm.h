#ifndef PARSE_ASM_H
#define PARSE_ASM_H
#include <stdint.h>

typedef char* String;

uint8_t* parse_r65asm(char* contents); // seperate statements by ';',
                                       // get opcode for each statement, add to a buffer of bytes, then return buffer
uint8_t get_opcode(char* statement); // run switch statement for instruction, 
                                     // use operands to decide variation, 
                                     // and return completed opcode (check validity in all steps)

#endif
