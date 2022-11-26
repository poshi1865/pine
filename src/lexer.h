#ifndef LEXER_H
#define LEXER_H

#include "commons.h"

typedef enum {
    TOKEN_HEAD, //This will be assigned to only one token which will point to the head of the token_stream
    TOKEN_IDENT, //Identifiers
    TOKEN_PUNCT, //Punctuation
    TOKEN_KEYWORD, //Keywords
    TOKEN_STR, //String literals
    TOKEN_NUM, //Numeric literals
    TOKEN_EOF, //End of file
    TOKEN_OPERATOR //Operators
} TokenType;

struct Token {
    TokenType type;
    char value[100]; 
    struct Token* next_token;
};


void init_token_stream();

struct Token get_next_token(FILE* source_file);

char get_next_char(FILE* source_file); 

void retract();

bool is_keyword(char* st);

#endif

