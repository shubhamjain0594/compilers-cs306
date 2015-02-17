all:    lex.cc parse.cc main.cc Scanner.h Scannerbase.h Scanner.ih Parser.h Parserbase.h Parser.ih
	sed -i '19 a\ int count = 0;' Parser.h;
	g++   --std=c++0x lex.cc parse.cc main.cc;
	./a.out < test-assembly > digraph.gv;
	sed -i '1 i\Digraph g{ ordering=out;' digraph.gv;
	echo "}" >> digraph.gv;
	dot -Tps digraph.gv -o graph1.ps;
	evince graph1.ps;


	# egrep 'nextToken|reduce' junk
        

lex.cc: lex.l Scanner.ih 
	rm -f Scanner.*
	flexc++ lex.l; 
	sed -i '/include/a #include "Parserbase.h"' Scanner.ih; 

parse.cc: parse.y Parser.ih Parser.h Parserbase.h
	rm -f Parser.*;
	bisonc++  parse.y; 
#	bisonc++   --construction -V parse.y; 
#	sed -i '/ifndef/a #include "tree_util.hh"' Parserbase.h;
#	sed -i '/ifndef/a #include "tree.hh"' Parserbase.h;
#	./sedscript
     

Parser.ih: parse.y
Parser.h:  parse.y
Parserbase.h: parse.y
Scanner.ih: lex.l
Scanner.h: lex.l
Scannerbase.h: lex.l

clear:
	rm -f Parser*
	rm -f Scanner*
	rm -f graph.ps
