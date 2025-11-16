#include "asm_loader.h" 
#include "parse_6502.h" 
#include "write_program.h" 
#include "tokenize_asm.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("Please specify target .s file.\n");
        goto catch;
    }
    
    char* contents = get_contents(argv[1]);
    if(contents == NULL) {
        printf("Loader error.\n");
        goto catch;
    }
    Token* tokens = tokenize(contents);
    Token token;
    int i = 0;
    while((token = tokens[i]).type != NULL) {
        i++;
        char* token_type;
        switch(token.type) {
            case REGISTER: token_type = "Register"; break;
            case INT_LITERAL: token_type = "Int literal"; break;
            case ADDRESS: token_type = "Address"; break;
            case DIRECTIVE: token_type = "Directive"; break;
            case INSTRUCTION: token_type = "Instruction"; break;
            case LABEL: token_type = "Label"; break;
            case COMMENT: token_type = "Comment"; break;
        }
        printf("[%s, %s]\n", token_type, token.value);
    }


    if(tokens == NULL) {
        printf("Analysis error.\n"); 
        goto catch;
    }
    uint8_t* rom_bytes = parse_6502(tokens);
    if(rom_bytes == NULL) {
        printf("Assembler error.\n");
        goto catch;
    } 
    if(write_rom(rom_bytes) == FAILED_WRITE) {
        printf("ROM write error.\n");
        goto catch;
    }
    printf("Assembled target 6502 assembly to ROM.\n");
    
    return EXIT_SUCCESS;
    catch: return EXIT_FAILURE;
}