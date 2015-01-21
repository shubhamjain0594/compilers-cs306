all:    lex.cc  main.cc 
	g++   --std=c++0x lex.cc main.cc

lex.cc: lex.l 
	rm -f Scanner.*
	flexc++ lex.l; 
	sed -i '/int lex()/r enums' Scanner.h