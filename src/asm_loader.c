#include "asm_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_contents(char* r65asm_path) {
    
    char* string_buf = NULL;
    int buf_chars = 0;

    FILE* file = fopen(r65asm_path, "r");
    if(file == NULL) {
        printf("Could not open target file.\n");
        return NULL;
    }
    
    char* _line_buf = NULL;
    char* line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_chars = 0;
    int line_count = 0;
    
    while ((line_chars = getline(&_line_buf, &line_buf_size, file)) != -1) {
        if(_line_buf[line_chars - 1] == '\n') line_chars--;
        line_chars++;
        line_buf = malloc(line_chars * sizeof(char));
        for(int i = 0; i < line_chars - 1; i++) {
            line_buf[i] = _line_buf[i];
        }
        line_buf[line_chars - 1] = '\t';

        if(line_count == 0) {
            if(strcmp(line_buf, "__R65A__\t") != 0) {
                printf("Missing __R65A__ header.\n");
                return NULL;
            }
        }
        if(line_count != 0 && line_chars != 0) {
            buf_chars += line_chars;
            string_buf = realloc(string_buf, (buf_chars * sizeof(char)));
            for(int i = 0; i < line_chars; i++) {
                if(line_buf[i] != '\n') {
                    string_buf[i + (buf_chars - line_chars)] = line_buf[i];
                }
            }
            string_buf[buf_chars] = '\0';
        }
       
        free(line_buf);
        line_buf = NULL;
        line_count++;
    }

    if(line_count == 0) {
        printf("Could not read file contents.\n");
        return NULL;
    } else if(line_count == 1) {
        printf("There is nothing to assemble.\n");
        return NULL;
    }

    free(_line_buf);
    fclose(file);

    return string_buf;
}
