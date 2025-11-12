#include "parse_r65.h"
#include "tokenize_asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* @ TODO:
    -Safety checks
    -Optimization
    -Memory safety
    -Create lexical analizer for tokenization
    -Keep assembly parser for generating opcodes
    -Write bytes
*/
Label* labels = NULL;
int labelsc = 0;

uint8_t* parse_r65(Statement* statements) {
    // create a buffer
    // get opcodes for each statements
    return NULL;
}

Opcode_info get_opcode(Statement statement, uint16_t offset) { // if null return, then return null
    Opcode_info opcode_info;
    opcode_info.opcode = 0x0;
    opcode_info.bytes = 0;

    int optypes_c[5] = {0,0,0,0,0};
    int operandsc = statement.tokensc - 1;
    Token* tokens = statement.tokens;
    char* instruction = NULL;

    Token maj_token = tokens[0];
    switch(maj_token.type) {
        case SHORT_HAND:
            instruction = maj_token.value;
            optypes_c[3]++;
            break;
        case LABEL:
            labelsc++;
            labels = realloc(labels, labelsc * sizeof(Label));
            labels[labelsc - 1].label = tokens[0].value;
            optypes_c[4]++;
            break;
        default:
            printf("Major token is not a label or instruction.\n");
            return opcode_info;
    }

    for(int i = 0; i < operandsc; i++) {
        Token operand = tokens[i + 1];
        if(!(operand.type == REGISTER || operand.type == INT_LITERAL || operand.type == ADDRESS)) {
            printf("Token is not an operand.\n");
            return opcode_info;
        } 
    }

    return opcode_info;
}