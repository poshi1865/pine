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
    int c;
    int i = 0;

    char token_buffer[100];

    int state = 0;
    char ch;
    while (ch != EOF) {
        switch (state) {
            case 0:
                ch = get_next_char(source_file);
                if (isalpha(ch)) {
                    state = 1;
                    token_buffer[i] = ch;
                    i++;
                }
                else {
                    state = 3;
                }
                break;

            case 1:
                ch = get_next_char(source_file);
                if (isalpha(ch) || isdigit(ch)) {
                    state = 1;
                    token_buffer[i] = ch;
                    i++;
                }
                else {
                    state = 2;
                }
                break;

            case 2:
                retract();
                for (int a = 0; a < inp_ptr; a++) {
                    printf("%c", input_buffer[a]);
                }
                printf("\n");
                state = 3;

                //Reset token_buffer
                for (int x = 0; x < 100; x++) token_buffer[x] = '\0';
                break;

            //whitespace
            case 3:
                ch = get_next_char(source_file);
                printf("Next char:%cs\n", ch);
                ch = get_next_char(source_file);
                printf("Next char:%cs\n", ch);
                exit(0);
                break;


            default:
                printf("DEFAULT\n");
                break;
        }
    }
}
