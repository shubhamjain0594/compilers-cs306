all:   clean lex.cc parse.cc main.cc
	./sedscript
	g++  -g --std=c++11 lex.cc parse.cc main.cc;
	./a.out < ${IP} > code.asm;
	# machine.cc code.asm
	g++ -g3 -O0 -m32 machine.cc -o ${OP}

lex.cc: lex.l  Scanner.ih
	flexc++ lex.l; 
#	sed -i '/include/a #include "Parserbase.h"' Scanner.ih; 

parse.cc: parse.y Parser.ih 
	bisonc++ --construction  parse.y; 
#	bisonc++   --construction -V parse.y; 
#	sed -i '/insert preincludes/a #include "headers.cc"' Parserbase.h;
#	sed -i '/include "Parser.h"/a #include "definitions.cc"' Parser.ih;

.PHONY: clean
clean:
	rm -f Scanner*
	rm -f Parser*
Parser.ih: parse.y
Parser.h:  parse.y
Parserbase.h: parse.y
Scanner.ih: lex.l
Scanner.h: lex.l
Scannerbase.h: lex.l
