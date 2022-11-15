#ifndef LEXER_H
#define LEXER_H

#include "commons.h"

typedef enum {
    TK_IDENT, //Identifiers
    TK_PUNCT, //Punctuation
    TK_KEYWORD, //Keywords
    TK_STR, //String literals
    TK_NUM, //Numeric literals
    TK_EOF, //End of file
} TokenType;

struct Token {
    TokenType type;
    char* value; 
};

void print_tokens(FILE* source_file);

char get_next_char(FILE* source_file); 

void retract();

#endif

