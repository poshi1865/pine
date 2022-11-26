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

#define INPUT_BUFFER_SIZE 100000

static char input_buffer[INPUT_BUFFER_SIZE];
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

bool is_keyword(char* st) {
    const int number_of_keywords = 6;
    const int max_size_of_keyword = 10;
    //TODO: fix the warning caused by the below line
    char keywords[number_of_keywords][max_size_of_keyword] = {"int", "print", "if", "else", "while", "for"};
    for (int i = 0; i < number_of_keywords; i++) {
        if (strcmp(keywords[i], st) == 0) return true; 
    }
    return false;
}

struct Token get_next_token(FILE* source_file) {
    struct Token token;
    int token_buffer_pointer = 0;

    char token_buffer[100] = {'\0'};

    int state = 0;
    char ch;
    while (ch != EOF) {
        switch (state) {

            //Start state
            case 0:
                ch = get_next_char(source_file);

                if (isalpha(ch)) {
                    state = 1;
                    token_buffer[token_buffer_pointer++] = ch;
                }
                else if (ch == ' ' || ch == '\t' || ch == '\n') {
                    state = 0;
                }
                //strings
                else if (ch == '"') {
                    state = 4;
                }
                else if (ch == '(' || ch == '{' || ch == '}' || ch == ')' || ch == ';') {
                    no_of_tokens++;

                    char ch_converted_to_string[2] = "\0";
                    ch_converted_to_string[0] = ch; //convert ch to a string

                    //create a new token
                    token.type = TOKEN_PUNCT;
                    strcpy(token.value, ch_converted_to_string);

                    state = 0;

                    return token;

                }

                else if (ch == '>' || ch == '<' || ch == '=' || ch == '!') {
                    state = 2;
                }

                else if (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '%') {
                    no_of_tokens++;

                    char ch_converted_to_string[2] = "\0";
                    ch_converted_to_string[0] = ch; //convert ch to a string
                                                    
                    token.type = TOKEN_OPERATOR;
                    strcpy(token.value, ch_converted_to_string);

                    return token;
                }

                else if (isdigit(ch)) {
                    state = 3;
                    token_buffer[token_buffer_pointer++] = ch;
                }

                else if (ch == EOF) break;

                else {
                    printf("First character of file is not a letter");
                    exit(1);
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

                    strcpy(token.value, token_buffer);
                    if (is_keyword(token.value)) {
                        token.type = TOKEN_KEYWORD;
                    }
                    else {
                        token.type = TOKEN_IDENT;
                    }


                    state = 0;
                    
                    return token;
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
                token.type = TOKEN_OPERATOR;
                strcpy(token.value, token_buffer);

                state = 0;
                return token;
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
                    token.type = TOKEN_NUM;
                    strcpy(token.value, token_buffer);

                    state = 0;
                    return token;
                }
                break;

            //Strings
            case 4:
                ch = get_next_char(source_file);
                if (ch == '"') {
                    no_of_tokens++;
                    token.type = TOKEN_STR;
                    strcpy(token.value, token_buffer);

                    state = 0;
                    return token;
                }
                else {
                    state = 4;
                    token_buffer[token_buffer_pointer++] = ch;
                }
                break;

            default:
                printf("ENTERED DEFAULT WHILE SCANNING INPUT\n");
                break;
        }
    }
    token.type = TOKEN_EOF;
    return token;
}
