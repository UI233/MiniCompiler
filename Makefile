clean:
	rm -rf *.o
	rm lex.yy.c

lexer:  lex.yy.o lexertest.o token.h
	cc -o lexer lex.yy.o lexertest.o

lexertest.o: lexertest.c token.h
	cc -c lexertest.c

lex.yy.o: lex.yy.c
	cc -c lex.yy.c

lex.yy.c: lexer.l token.h
	lex lexer.l