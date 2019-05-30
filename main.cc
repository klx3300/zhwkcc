#include <cstdio>
#include "semantic/mini_c.sem.hpp"

extern FILE* yyin;
extern int yylineno;

int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return -1;
	yyparse();
	return 0;
}
