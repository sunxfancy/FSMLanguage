%{

#include <stdlib.h>
#include "Module.h"
#include "parser.hpp"
#include "lex.h"
using namespace std;
using namespace fir;

void yyerror (yyscan_t locp, Module *mod, char const *msg);

%}

%define api.pure full
%lex-param {void *scanner}
%parse-param {void *scanner}{Module *mod}

%define parse.trace
%define parse.error verbose
%code requires
{
#include "Module.h"
}

%union {
	FSMVectorUP fsm_vup;
	FSMUP fsm_up;
	StringVectorUP string_vup;
	StatementVectorUP statement_vup;
	StatementUP statement_up;
	StateUP state_up;
	TransitionVectorUP transition_vup;
	const char *str;
	int token;
}

%token <token> CEQ CNE CGE CLE TO
%token <str> ID STRING 

%type <fsm_vup> Program FSMs 
%type <fsm_up> FSM
%type <string_vup> Args
%type <statement_vup> Statements
%type <statement_up> Statement
%type <state_up> Config
%type <transition_vup> Transitions

%start Program

%%

Program 
	: FSMs { mod->root = move($1); }
	;

FSMs
	: FSMs FSM { $1->push_back($2.release()); }
	| FSM { FSMVectorUP fsm_ptr(new FSMVector()); 
			fsm_ptr->push_back($1.release()); $$ = move(fsm_ptr); }
	;

FSM
	: ID '(' Args ')' ':' Args '{' Statements '}' 
		{
			FSMUP fsm(new FSM($1, $3, $6, $8));
			$$ = move(fsm);
		}
	;

Args
	: Args ',' ID 
		{
			$$->push_back($3);
		}
	| ID {
			StringVectorUP svup(new StringVector());
			svup->push_back($1); $$ = move(svup);
		}
	;

Statements
	: Statements Statement {
		$1->push_back($2.release());
		$$ = move($1); 
	}
	| Statement {
		StatementVectorUP svup(new StatementVector());
		svup->push_back($1);
		$$ = move(svup);
	}
	;

Statement
	: Config { $$ = move($1); }
	| Transitions { $$ = move($1); }
	;

Config
	: ID ':' States { StateUP sup(new State($1, $3)); $$ = move(sup); }
	;

States
	: States ',' ID 
	| ID
	;

Transitions
	: Transitions Condition TO ID
	| ID Condition TO ID
	;

Condition
	: '(' Exprs ')'
	| '(' ')'
	| %empty
	;

Exprs
	: Exprs ',' Expr
	| Expr
	;

Expr
	: Expr CEQ Expr
	| Expr CNE Expr
	| Expr CLE Expr
	| Expr CGE Expr
	| Expr '<' Expr 
	| Expr '>' Expr 
	| Expr '+' Expr 
	| Expr '-' Expr 
	| Expr '*' Expr 
	| Expr '/' Expr 
	| Expr '%' Expr 
	| Expr '^' Expr 
	| Expr '&' Expr 
	| Expr '|' Expr 
	| '!' Expr
	| '(' Expr ')'
	;
%%

void yyerror (yyscan_t locp, Module *mod, const char *msg) {
	fprintf(stderr, "> %s\n", msg);
	// TODO: add line number and detail
	// fprintf(stderr, "Parser Cfg line %d: ", locp);
	// fprintf(stderr, "error %s \n", yytext);
	exit(1);
}
