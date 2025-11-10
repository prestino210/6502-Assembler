// entry point, use target arg to output r65 rom
#include "asm_loader.h" // load r65 asm
#include "parse_asm.h" // parse r65 asm -> r65 rom bytes
#include "write_r65.h" // write bytes to r65 rom
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    if(argc > 1) {
        char* contents = get_contents(argv[1]);
        if(contents == NULL) {
            printf("Could not verify R65 assembly.\n");
            return EXIT_FAILURE;
        }
        uint8_t* rom_bytes = parse_r65asm(contents);
        if(rom_bytes == NULL) {
            printf("Incorrect assembly syntax in target file.\n");
            return EXIT_FAILURE;
        }
        if(write_rom(rom_bytes) == FAILED_WRITE) {
            printf("Could not write ROM file.\n");
            return EXIT_FAILURE;
        }
        printf("Assembled target R65 assembly to ROM.\n");
        return EXIT_SUCCESS;
    } else {
        printf("Please specify target file.\n");
        return EXIT_FAILURE;
    }
}