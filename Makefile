CC=clang
CCFLAGS= -O2 -g -Wall

source_files= src/pine.c src/lexer.c

ekans: $(source_files)
	$(CC) -g -o pine $(source_files)

