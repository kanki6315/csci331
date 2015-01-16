CC = g++

CFLAGS = 

all: cm

lex.yy.c: scan.lex compiler.h support.h 
	flex scan.lex

y.tab.c: parse.yac lex.yy.c support.h 
	yacc parse.yac

y.tab.o: y.tab.c
	$(CC) $(CFLAGS) -c y.tab.c

support.o: compiler.h support.h support.cc
	$(CC) $(CFLAGS) -c support.cc

Semantic.o: compiler.h support.h Semantic.h Semantic.cc
	$(CC) $(CFLAGS) -c Semantic.cc

Generate.o: compiler.h Generate.h Generate.cc
	$(CC) $(CFLAGS) -c Generate.cc

main.o: compiler.h support.h Semantic.h Generate.h main.c
	$(CC) $(CFLAGS) -c main.c

cm: y.tab.o main.o support.o Semantic.o Generate.o
	$(CC) $(CFLAGS) main.o support.o Semantic.o Generate.o y.tab.o -o cm
clean:
	-rm cm lex.yy.c y.tab.c *.o
