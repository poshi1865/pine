#ifndef LEXER_H
#define LEXER_H

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

void print_tokens();

#endif

