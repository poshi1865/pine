/* Lexical Analysis is the first phase of compilation.
 * The Lexer does the task of taking in a pine source file as input and outputs tokens
 * The lexer will be called by the parser as a subroutine each time a token is needed
 *
 * There are 4 kinds of tokens: Keyword, Identifier, Constant (123, 12.45, 1.2E3), Sign ('(', '<' , "<=" etc)
 *
 * The Token struct is defined in the lexer.h header file
 * */ 

#include "lexer.h"
#include <stdio.h>

void get_next_token() {
}

void print_tokens(FILE* program) {
    int c;
    int i = 0;
    char token_buffer[100];
    while ((c = getc(program)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            printf("%s\n", token_buffer);
            i = 0;
            for (int x = 0; x < 100; x++) token_buffer[x] = '\0';
            continue;
        }
        else {
            token_buffer[i] = c;
            i++;
        }
    }
}
