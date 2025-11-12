#include "tokenize_asm.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

Statement* tokenize(char* contents) {
    if(contents == NULL) {
        printf("No content to parse.\n");
        return NULL;
    }
    uint8_t* r65_bytes = NULL;
    char** str_statements = NULL;
    int str_statementsc = 0;
    char* str_statement_buf = NULL;
    int statement_buf_chars = 0;
    bool str_is_statement = false;
    int i = 0;

    while(contents[i] != '\0') {
        if(str_is_statement && (contents[i] == '\t')) { 
            str_statementsc++;
            str_statements = realloc(str_statements, str_statementsc * sizeof(char*));
            char* buf = NULL;
            switch(contents[i]) {
                case '\t':
                    buf = malloc((statement_buf_chars + 1) * sizeof(char));
                    buf[statement_buf_chars] = '\0';
                    break;
                case ':':
                    buf = malloc((statement_buf_chars + 2) * sizeof(char));
                    buf[statement_buf_chars] = ':';
                    buf[statement_buf_chars + 1] = '\0';
                    break;
            }
            
            for(int j = 0; j < statement_buf_chars; j++) {
                buf[j] = str_statement_buf[j];
            }
            str_statements[str_statementsc - 1] = buf;
            free(str_statement_buf);
            str_statement_buf = NULL;
            str_is_statement = false;
            statement_buf_chars = 0;
        } else {
            if(contents[i] != ' ' && contents[i] != '\t') str_is_statement = true;
            statement_buf_chars++;
            str_statement_buf = realloc(str_statement_buf, statement_buf_chars * sizeof(char));
            str_statement_buf[statement_buf_chars - 1] = contents[i];
        }
        i++;
    }

    Statement* statements = malloc(str_statementsc * sizeof(Statement));
    for (int i = 0; i < str_statementsc; i++) {
        statements[i].tokens = NULL;
        statements[i].tokensc = 0;
    }

    int statementsc = str_statementsc;
    for(int i = 0; i < str_statementsc; i++) {
        int j = 0;
        char c = str_statements[i][j];
        while(c != '\0') {
            Token token = {0};
            token.value = malloc(sizeof(char));
            token.value[0] = '\0';
            token.type = EXCLUDE;
            c = str_statements[i][j];
            if(c == '_' || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                int k = 0;
                char* str = NULL;
                char _c = str_statements[i][j];
                while(!(_c == ' ' || _c == ':' || _c == ',' || _c == '\0')) {
                    if(!(_c == '_' || (_c >= '0' && _c <= '9') || (_c >= 'a' && _c <= 'z') || (_c >= 'A' && _c <= 'Z'))) {
                        printf("Missing space.\n");
                        return NULL;
                    }

                    k++; j++;
                    str = realloc(str, k * sizeof(char));
                    str[k - 1] = _c;
                    _c = str_statements[i][j];
                    if(_c == '\0') break;
                }
                str = realloc(str, (k + 1) * sizeof(char));
                str[k] = '\0';
                switch(_c) {
                    case ',':
                        if(k > 1) {
                            token.type = SHORT_HAND;
                        } else {
                            token.type = REGISTER;
                        }
                        break;
                    case ' ':
                        if(k > 1) {
                            token.type = SHORT_HAND;
                        } else {
                            token.type = REGISTER;
                        }
                        break;
                    case ':':
                        token.type = LABEL; 
                        break;
                    case '\0':
                        if(k > 1) {
                            token.type = SHORT_HAND;
                        } else {
                            token.type = REGISTER;
                        }
                        break;
                }
                token.value = str;
            } else if(c == '#' || c == '$') {
                bool is_addr = ((c == '$') ? true : false);
                char* str = NULL;
                int k = 0;
                char _c = str_statements[i][j];
                
                while(!(_c == ')' || _c == '\0' || _c == ' ' || _c == ':' || _c == ',')) {
                    if(!is_addr & k == 1 && _c != '$') {
                        printf("Invalid syntax.\n");
                        return NULL;
                    }
                    if(k > 1 && !is_addr & !((_c >= 'A' && _c <= 'Z') || (_c >= 'a' && c <= 'z') || (_c >= '0' && _c <= '9'))) {
                        printf("Invalid integer.\n");
                        return NULL;
                    }
                    if(k > 0 && is_addr & !((_c >= 'A' && _c <= 'Z') || (_c >= 'a' && c <= 'z') || (_c >= '0' && _c <= '9'))) {
                        printf("Invalid address.\n");
                        return NULL;
                    }
                    
                    k++; j++;
                    str = realloc(str, k * sizeof(char));
                    str[k - 1] = _c;
                    _c = str_statements[i][j];
                }
                str = realloc(str, (k + 1) * sizeof(char));
                str[k] = '\0';
    
                switch(is_addr) { // remove the int buf since in writing it will all be hex strings converting into raw data
                    case false:
                        if(k > 2) {
                            token.type = INT_LITERAL;
                            token.value = str;
                        } else {
                            printf("Invalid integer.\n");
                            return NULL;
                        }
                        break;
                    case true:
                        token.type = ADDRESS;
                        token.value = str;
                        break;
                }

            } else if(c == ';') {
                j++;
                int k = 0;
                char* str = NULL;
                char _c = str_statements[i][j];
                while(_c != '\0') {

                    k++; j++;
                    str = realloc(str, k * sizeof(char));
                    str[k - 1] = _c;
                    _c = str_statements[i][j];
                }
                str = realloc(str, (k + 1) * sizeof(char));
                str[k] = '\0';
                token.type = COMMENT;
                token.value = str;
            } else if(c == '.') {
                int k = 0;
                char* str = NULL;
                char _c = str_statements[i][j];
                while(!(_c == ' ' || _c == ':' || _c == ',' || _c == '\0')) {
                    if(k > 0 && (!(_c == '_' || (_c >= '0' && _c <= '9') || (_c >= 'a' && _c <= 'z') || (_c >= 'A' && _c <= 'Z')))) {
                        printf("Missing space.\n");
                        return NULL;
                    }

                    k++; j++;
                    str = realloc(str, k * sizeof(char));
                    str[k - 1] = _c;
                    _c = str_statements[i][j];
                    if(_c == '\0') break;
                }
                str = realloc(str, (k + 1) * sizeof(char));
                str[k] = '\0';
                switch(_c) {
                    case ',':
                        printf("Invalid directive.\n");
                        return NULL;
                        //error
                        break;
                    case ':':
                        // error
                        printf("Invalid directive.\n");
                        return NULL;
                        break;
                    default:
                        token.type = DIRECTIVE;
                        token.value = str;
                        break;
                }
                
            } else {
                token.type = EXCLUDE;
                j++;
            }

            if(token.type != EXCLUDE) {
                Statement* statement = &(statements[i]);
                statement->tokensc++;
                statement->tokens = realloc(statement->tokens, statement->tokensc * sizeof(Token));
                statement->tokens[statement->tokensc - 1] = token;
            }
        }
    }

    printf("Tokens by line:\n");
    for(int i = 0; i < statementsc; i++) {
        printf("Line %d: ", i+1);
        for(int j = 0; j < statements[i].tokensc; j++) {
            
            switch(statements[i].tokens[j].type) {
                case REGISTER:
                    printf("[Register: ");
                    break;
                case DIRECTIVE:
                    printf("[Directive: ");
                    break;
                case INT_LITERAL:
                    printf("[Int literal: ");
                    break;
                case ADDRESS:
                    printf("[Address: ");
                    break;
                case SHORT_HAND:
                    printf("[Short hand: ");
                    break;
                case COMMENT:
                    printf("[Comment: ");
                    break;
                case LABEL:
                    printf("[Label: ");
                    break;
            }
            if(j == statements[i].tokensc -1) {
                printf("%s]", statements[i].tokens[j].value);
            } else {
                printf("%s], ", statements[i].tokens[j].value);
            }
        }
        printf("\n");
    }

    return statements;
}