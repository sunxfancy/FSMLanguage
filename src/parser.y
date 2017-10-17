%{

void yyerror(const char *s);

#include <stdlib.h>
#include "State.h"
#include "BNFParser.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
extern int yyleng;
extern State* root;
extern BNFParser* bnfparser;

#define YYERROR_VERBOSE 1

%}


%union {
	State *s;
	char *str;
}


%token <str> ID STRING TO GE LE

%type <s> FSMs 

%start FSMs

%%

FSMs
	: FSMs FSM  {}
	| FSM {}
	;




%%

void yyerror(const char* s){
	fprintf(stderr, "%s \n", s);
	fprintf(stderr, "Parser Cfg line %d: ", yylineno);
	fprintf(stderr, "error %s \n", yytext);
	exit(1);
}
