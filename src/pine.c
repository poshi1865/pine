#include "commons.h"
#include "lexer.h"

char* translate(int n) {
    if (n == 0) return "TOKEN_HEAD";
    if (n == 1) return "TOKEN_IDENT";
    if (n == 2) return "TOKEN_PUNCT";
    if (n == 3) return "TOKEN_KEYWORD";
    if (n == 4) return "TOKEN_STR";
    if (n == 5) return "TOKEN_NUM";
    if (n == 6) return "TOKEN_EOF";
    if (n == 7) return "TOKEN_OPERATOR";
    return "UNDEFINED";
}

int main(int argc, char** argv) {
    //For now we can pass in only 1 input file to the compiler
    if (argc < 2) {
        printf("No input file!\n");
        exit(1);
    }

    FILE* source_file;

    source_file = fopen(argv[1], "r");

    if (source_file == NULL) {
        printf("Could not open file %s\n", argv[1]);
        exit(1);
    }
    
    struct Token t;
    int c = 0;
    while ((t = get_next_token(source_file)).type != TOKEN_EOF) {
        printf("Token: %s\t\t", t.value);
        printf("Type: %s\n", translate(t.type));
        c++;
    }
    printf("%d\n", c);

    //close the file
    fclose(source_file);
    return 0;
}
