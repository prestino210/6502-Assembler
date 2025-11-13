// entry point, use target arg to output r65 rom
#include "asm_loader.h" // load r65 asm
#include "parse_r65.h" // parse r65 asm -> r65 rom bytes
#include "write_r65.h" // write bytes to r65 rom
#include "tokenize_asm.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
// @todo: tell user the line and character in errors
int main(int argc, char** argv) {
    if(argc > 1) {
        char* contents = get_contents(argv[1]);
        if(contents == NULL) {
            printf("Loader error.\n");
            return EXIT_FAILURE;
        }
        Statement* lexic_statements = tokenize(contents);
        if(lexic_statements == NULL) {
            printf("Analysis error.\n"); // un comment
            return EXIT_FAILURE;
        }
        uint8_t* rom_bytes = parse_r65(lexic_statements);
        if(rom_bytes == NULL) {
            //printf("Assembler error.\n");
            return EXIT_FAILURE;
        } 
        if(write_rom(rom_bytes) == FAILED_WRITE) {
            printf("ROM write error.\n");
            return EXIT_FAILURE;
        }
        printf("Assembled target R65 assembly to ROM.\n");
        return EXIT_SUCCESS;
    } else {
        printf("Please specify target file.\n");
        return EXIT_FAILURE;
    }
}