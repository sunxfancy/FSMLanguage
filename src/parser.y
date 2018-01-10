%{

#include <stdlib.h>
#include "Module.h"

#ifdef _WIN32
/* windows compatibility case */  
#define YY_NO_UNISTD_H
#include <io.h>  
#define isatty _isatty  
#define fileno _fileno  
#endif

#include "parser.hpp"
#include "lex.h"
using namespace std;
using namespace fsm;

void yyerror (yyscan_t locp, Module *mod, char const *msg);

%}

%define api.pure full
%lex-param {void *scanner}
%parse-param {void *scanner}{fsm::Module *mod}

%define parse.trace
%define parse.error verbose
%code requires
{
#include "Module.h"
}

%union {
	fsm::FSMUPVectorUP fsm_vup;
	fsm::FSMUP fsm_up;
	fsm::StringVectorUP string_vup;
	fsm::StatementUPVectorUP statement_vup;
	fsm::StatementUP statement_up;
	fsm::StateUP state_up;
	fsm::TransitionUPVectorUP transition_vup;
	const char *str;
	int token;
}

%token <token> CEQ CNE CGE CLE TO
%token <str> ID STRING CONDITION

%type <fsm_vup> Program FSMs 
%type <fsm_up> FSM
%type <string_vup> Args States
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
	: FSMs FSM { $1->push_back(move($2)); }
	| FSM { FSMUPVectorUP fsm_ptr(new FSMUPVector()); 
			fsm_ptr->push_back(move($1)); $$ = move(fsm_ptr); }
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
		$1->push_back(move($2));
		$$ = move($1); 
	}
	| Statement {
		StatementUPVectorUP svup(new StatementUPVector());
		svup->push_back(move($1));
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
	: States ',' ID { $1->push_back($3); $$ = move($1); }
	| ID { StringVectorUP svup(new StringVector()); svup->push_back($1); $$ = move(svup); }
	;

Transitions
	: Transitions CONDITION TO ID { TransitionUP tup(new Transition($1->back()->EndState, $4, $2));
		 							$1->push_back(move(tup)); $$ = move($1); }
	| ID CONDITION TO ID { TransitionUPVectorUP tvup(new TransitionUPVector()); 
						   TransitionUP tup(new Transition($1, $4, $2));
						   tvup->push_back(move(tup)); $$ = move(tvup); }
	;

/*
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
*/
%%

void yyerror (yyscan_t locp, Module *mod, const char *msg) {
	fprintf(stderr, "> %s\n", msg);
	// TODO: add line number and detail
	// fprintf(stderr, "Parser Cfg line %d: ", locp);
	// fprintf(stderr, "error %s \n", yytext);
	exit(1);
}
