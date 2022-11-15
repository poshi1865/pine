#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

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
    
    print_tokens(source_file);

    //close the file
    fclose(source_file);
    return 0;
}
