/* Lexical Analysis is the first phase of compilation.
 * The Lexer does the task of taking in a pine source file as input and outputs tokens
 * The lexer will be called by the parser as a subroutine each time a token is needed
 *
 * There are 4 kinds of tokens: Keyword, Identifier, Constant (123, 12.45, 1.2E3), Sign ('(', '<' , "<=" etc)
 *
 * The Token struct is defined in the lexer.h header file
 * */ 

#include "commons.h"
#include "lexer.h"

static char input_buffer[1000];
static int inp_ptr = 0;
static int input_buffer_size = 0;

int no_of_tokens = 0;

char get_next_char(FILE* source_file) {
    if (inp_ptr < input_buffer_size) {
        return input_buffer[inp_ptr++];
    }
    else {
        char c = getc(source_file);
        input_buffer_size++;
        return input_buffer[inp_ptr++] = c;
    }
}

void retract() {
    inp_ptr--;
}

void print_tokens(FILE* source_file) {
    int token_buffer_pointer = 0;

    char token_buffer[100] = {'\0'};

    int state = 0;
    char ch;
    while (ch != EOF) {
        switch (state) {
            case 0:
                ch = get_next_char(source_file);

                if (isalpha(ch)) {
                    state = 1;
                    token_buffer[token_buffer_pointer++] = ch;
                }
                else if (ch == ' ' || ch == '\t' || ch == '\n') {
                    state = 0;
                }
                else if (ch == '(' || ch == '{' || ch == '}' || ch == ')' || ch == ';'
                        || ch == '"') {
                    no_of_tokens++;
                    printf("Token %d: %c\n", no_of_tokens, ch);
                    state = 0;
                }

                else if (ch == '>' || ch == '<' || ch == '=' || ch == '!') {
                    state = 2;
                }

                else if (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '%') {
                    no_of_tokens++;
                    printf("Token %d: %c\n", no_of_tokens, ch);
                }

                else if (isdigit(ch)) {
                    state = 3;
                    token_buffer[token_buffer_pointer++] = ch;
                }

                else if (ch == EOF) break;

                else {
                    printf("First character of file is not a letter");
                    exit(0);
                }
                break;

            //Identifier
            case 1:
                ch = get_next_char(source_file);
                if (isalpha(ch) || isdigit(ch) || ch == '_') {
                    state = 1;
                    token_buffer[token_buffer_pointer++] = ch;
                }
                else if (token_buffer[0] != '\0'){
                    retract();
                    no_of_tokens++;
                    printf("Token %d: %s\n", no_of_tokens, token_buffer);

                    //Reset token_buffer and token_buffer_pointer
                    for (int x = 0; x < 100; x++) token_buffer[x] = '\0';
                    token_buffer_pointer = 0;

                    state = 0;
                }
                break;

            //Relational Operators
            case 2:
                //Greater than equals
                if (ch == '>') {
                    token_buffer[token_buffer_pointer++] = ch;
                    ch = get_next_char(source_file);
                    if (ch == '=') {
                        token_buffer[token_buffer_pointer++] = ch;
                    }
                    else {
                        retract();
                    }
                }
                //Less than equals
                else if (ch == '<') {
                    token_buffer[token_buffer_pointer++] = ch;
                    ch = get_next_char(source_file);
                    if (ch == '=') {
                        token_buffer[token_buffer_pointer++] = ch;
                    }
                    else {
                        retract();
                    }
                }
                //Equal equal
                else if (ch == '=') {
                    token_buffer[token_buffer_pointer++] = ch;
                    ch = get_next_char(source_file);
                    if (ch == '=') {
                        token_buffer[token_buffer_pointer++] = ch;
                    }
                    else {
                        retract();
                    }
                }
                //Not equals
                else if (ch == '!') {
                    ch = get_next_char(source_file);
                    if (ch == '=') {
                        token_buffer[token_buffer_pointer++] = '!';
                        token_buffer[token_buffer_pointer++] = ch;
                    }
                    else {
                        retract();
                    }
                }
                no_of_tokens++;
                printf("Token %d: %s\n", no_of_tokens, token_buffer);

                //Reset token buffer
                for (int x = 0; x < 100; x++) token_buffer[x] = '\0';
                token_buffer_pointer = 0;

                state = 0;
                break;

            //Numbers
            case 3:
                ch = get_next_char(source_file);
                if (isdigit(ch)) {
                    state = 3;
                    token_buffer[token_buffer_pointer++] = ch;
                }
                else if (token_buffer[0] != '\0'){
                    retract();
                    no_of_tokens++;
                    printf("Token %d: %s\n", no_of_tokens, token_buffer);

                    //Reset token_buffer and token_buffer_pointer
                    for (int x = 0; x < 100; x++) token_buffer[x] = '\0';
                    token_buffer_pointer = 0;

                    state = 0;
                }
                break;

            default:
                printf("DEFAULT\n");
                break;
        }
    }
}
