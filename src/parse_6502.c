#include "parse_6502.h"
#include "tokenize_asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    ACCUM,
    IMM,
    ABS,
    ABS_X,
    ABS_Y,
    ZPG,
    ZPG_X,
    ZPG_Y,
    IMPL,
    RELATIVE,
    IND_X,
    IND_Y,
    IND
} ADDRESSING_MODE;

typedef struct {
    uint16_t offset;
    char* label;
} Label;


typedef struct {
    char* mnemonic;
    ADDRESSING_MODE addressing_mode;
    uint8_t byte;
    
} Opcode;

Opcode opcode_lookup(Token* tokens, int i) {

}

uint16_t str_uint16 (char* str) {
    uint16_t int16 = 0;
    char c;
    int i = 0;
    while((c = str[i]) != '\0') { i++;
        int val = 0;
        if((c >= '0') && (c <= '9')) {
            val = c - '0';
            goto int16;
        }  else if(c >= 'A' && c <= 'F') {
            val = c - 'A';
        } else if(c >= 'a' && c <= 'f') {
            val = c - 'A';
        } else {
            printf("Invalid hex.\n");
            goto _return; 
        }             
        val += 10;
    
        int16:
        int16 *= 16;
        int16 += val;
    }

    _return:
    return int16;
}

uint8_t str_uint8 (char* str) {
    return (uint8_t) str_int16(str);
}


Label* labels = NULL;
int labelsc = 0;
uint16_t org_offset = 0x0600;

uint8_t* parse_6502(Token* tokens) {
    uint8_t* prgm_bytes = NULL;
    uint16_t prgrm_offset = org_offset;

    // write string opcodes first (might be easier)
    // convert hex strings into data
    Token token;
    int i = 0;
    while((token = tokens[i]).type != NULL) {
        TOKEN_TYPE type = token.type;
        if(type == INSTRUCTION || type == DIRECTIVE) goto op;
        if(type == LABEL) goto label;
        goto loop;
        op:
        


        goto loop;
        label:
        Label label;
        label.label = token.value;
        label.offset = prgrm_offset;
        loop:
    }

    return prgm_bytes;
}

