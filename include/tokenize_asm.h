#ifndef TOKENIZE_ASM_H
#define TOKENIZE_ASM_H

typedef enum {
    REGISTER, // specify register
    INT_LITERAL, // pass to opcode
    ADDRESS, // pass to opcode
    DIRECTIVE, // tell parser something
    INSTRUCTION, // looks for args according to program OR tells parser to de-reference label
    LABEL, // store offset and de-reference later
    COMMENT, // parser does nothing then restarts after comments
    SYMBOL, // parser needs specific type
    INVALID // not passed
} TOKEN_TYPE;

typedef struct {
    TOKEN_TYPE type;
    char* value;
} Token;

Token* tokenize(char* contents);


#endif