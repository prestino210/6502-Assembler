#include "parse_r65.h"
#include "tokenize_asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#define S_DIRECTIVE 0
#define S_INSTRUCTION 1
#define S_LABEL 2
#define NO_BYTES -1
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
uint16_t prgm_offset = 0x0600;

uint8_t* parse_r65(Statement* statements) {
    // create a buffer
    // get opcodes for each statements
    uint8_t* r65_buffer = NULL;
    int bytes = 0;
    Statement statement = NULL;
    int i = 0;
    while((statement = statements[i]) != NULL) {
        Opcode_info opinfo = get_opcode(statement, (uint16_t)(prgm_offset+(bytes*sizeof(uint8_t))));
        if(opinfo == NULL) {
            printf("Parser error.\n");
            return NULL;
        }
        if(opinfo.bytes != NO_BYTES) {
            bytes += opinfo.bytes;
            r65_buffer = realloc(r65_buffer, sizeof(uint8_t) * bytes);
            for(int j = 0; j < opinfo.bytes; j++) {
                r65_buffer[bytes - opinfo.bytes + j] = opinfo.opcode[j];
            }
        }
    }
    return NULL;
}

bool is_symbol(Token token) {
    return (token.type == MNEMONIC || token.type == DIRECTIVE
        || token.type == COMMENT || token.type == LABEL);
}

// method to convert addresses and int literals into ints


Opcode_info get_opcode(Statement statement, uint16_t offset) { // if null return, then return null
    Opcode_info opcode_info;
    opcode_info.opcode = NULL;
    opcode_info.bytes = 0;
    Token* tokens = statement.tokens;
    int tokensc = statement.tokensc;
    int state_type = NO_BYTES;
    int _state_type = NO_BYTES;
    bool delta_state = false;
    char* symbol = NULL;
    char* _symbol = NULL;
    char* registers = NULL;
    int registersc = 0;
    char** int_literals = NULL;
    int int_literalsc = 0;
    char** addresses = NULL;
    int addressesc;

    for(int i = 0; i < tokensc; i++) {
        Token token = tokens[i];
        int state_type_temp = NO_BYTES;
        char* symbol_temp = token.value;
        bool is_symb = is_symbol(token);
        if(i == 0 && !is_symb) {
            printf("Invalid statement.\n");
            return NULL;
        } else if(i > 0 && is_symb && token.type != COMMENT) {
            if(!(tokens[0].type == LABEL && i == 1 && token.type != DIRECTIVE && token.type != LABEL)) {
                printf("Invalid statement.\n");
                return NULL;
            } else if(tokens[0].type == LABEL && i == 1 && token.type != DIRECTIVE && token.type != LABEL) {
                delta_state = true;
            }
        }
        switch(token.type) {
            case REGISTER:
                registersc++;
                registers = realloc(registers, registersc * sizeof(char));
                registers[registersc - 1] = token.value[0];
                break;
            case INT_LITERAL:
                int_literalsc++;
                int_literals = realloc(int_literals, int_literalsc * sizeof(char*));
                int_literals[int_literals - 1] = value;
                break;
            case ADDRESS:
                addressesc++;
                addresses = realloc(addresses, addressesc * sizeof(char*));
                addresses[addressesc - 1] = value;
                break;
            case DIRECTIVE:
                state_type_temp = S_DIRECTIVE;
                break;
            case INSTRUCTION:
                state_type_temp = S_DIRECTIVE;
                break;
            case LABEL:
                state_type_temp = S_LABEL;
                break;
            case COMMENT:
                opcode_info.bytes = NO_BYTES;
                return opcode_info;
                break;
        }

        if(state_type != NO_BYTES) {
            _state_type = state_type_temp;
        } else {
            state_type = state_type_temp;
        }

        if(symbol != NULL) {
            _symbol = symbol_temp;
        } else {
            symbol = symbol_temp;
        }
    }

    if(!delta_state) {
        
    } else {

    }

    return opcode_info;
}