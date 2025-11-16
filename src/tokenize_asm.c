#include "tokenize_asm.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_end_char(char c) {
    return (c == ')')  || (c == ',')
        || (c == '\n') || (c == ':')
        || (c == ' ')  || (c == ';');
}

bool is_register(char c) {
    return (c == 'A') || (c == 'X') || (c == 'Y');
}

TOKEN_TYPE get_type(char c) {
    TOKEN_TYPE type = INVALID;
    switch(c) {
        case '#':
            type = INT_LITERAL;
            break;
        case '$':
            type = ADDRESS;
            break;
        case '.':
            type = DIRECTIVE;
            break;
        case ';':
            type = COMMENT;
            break;
        default:
            if(((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9'))) {
                type = SYMBOL;
            }
            break;
    }
    return type;
}

Token* tokenize(char* contents) {
    Token* tokens = NULL;
    int tokens_size = 0;
    int tokensc = 0;
    char c;
    int i = 0;
    int col = 1;
    int line = 2;
    TOKEN_TYPE type = INVALID;
    char* value_buf = NULL;
    size_t value_buf_size = 0;
    int value_chars = 0;
    
    while((c = contents[i]) != '\0') { i++;
        
        bool is_end = (type == COMMENT) ? (c == '\n') : is_end_char(c);
        if(is_end && type != INVALID) {
            switch(c) {
                case '\n': line++; col = 1; break;
                case ':': 
                    if(type == SYMBOL || type == DIRECTIVE) {
                        type == LABEL;
                    } else {
                        goto fail;
                    }
                    break;
            }

            if(type == SYMBOL) {
                type = INSTRUCTION;
                if(value_chars == 1 && is_register(c)) { 
                    type = REGISTER;
                }
            }

            Token token;
            token.type = type;
            value_chars++;
            value_buf_size = value_chars * sizeof(char);
            value_buf = realloc(value_buf, value_buf_size);
            value_buf[value_chars - 1] = '\0';
            token.value = value_buf;

            tokensc++;
            tokens_size = tokensc * sizeof(Token);
            tokens = realloc(tokens, tokens_size);
            tokens[tokensc - 1] = token;

            if(c == ';')  {
                i--;
            } 
            type = INVALID;
            value_buf = NULL;
            value_chars = 0;
            value_buf_size = 0;

        } else {
            if(type == INVALID)  {
                type = get_type(c); 
                if(type != SYMBOL) goto skip;
            } else if(type != COMMENT) {
                TOKEN_TYPE _type = get_type(c);
                if(_type != SYMBOL) {
                    if(type == SYMBOL || type == DIRECTIVE) {printf("1");goto fail;}
                    if(type != INT_LITERAL) {printf("2"); goto fail;}
                    if(_type != ADDRESS)  {
                        printf("3");
                        goto fail;
                    } else {
                        goto skip;
                    }
                }
            }

            value_chars++;
            value_buf_size = value_chars * sizeof(char);
            value_buf = realloc(value_buf, value_buf_size);
            value_buf[value_chars - 1] = c;
            skip:
        }
        col++;
    }
    goto _return;

    fail:
    printf("Invalid character at (line %d, character %d)\n", line, col);
    printf("%c\n", c);
    tokens = NULL;
    _return:
    return tokens;
}

