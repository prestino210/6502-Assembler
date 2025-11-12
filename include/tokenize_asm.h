#ifndef TOKENIZE_ASM_H
#define TOKENIZE_ASM_H

typedef enum {
    REGISTER,
    INT_LITERAL,
    ADDRESS,
    SHORT_HAND, // Mnemonics and labels
    LABEL,
    COMMENT,
    EXCLUDE
} TOKEN_TYPE;

typedef struct {
    TOKEN_TYPE type;
    char* str;
    int value;
} Token;

typedef struct {
    int tokensc;
    Token* tokens;
} Statement;

Statement* tokenize(char* contents);


#endif