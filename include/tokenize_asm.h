#ifndef TOKENIZE_ASM_H
#define TOKENIZE_ASM_H

typedef enum {
    REGISTER,
    SYMBOL,
    INT_LITERAL,
    ADDRESS,
    DIRECTIVE,
    DIRECTIVE_LABEL,
    INSTRUCTION,
    LABEL,
    COMMENT,
    INVALID
} TOKEN_TYPE;

typedef struct {
    TOKEN_TYPE type;
    char* value;
} Token;

Token* tokenize(char* contents);


#endif