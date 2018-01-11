%{

#include <stdlib.h>
#include <memory>
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
	fsm::FSMPVectorP fsm_vup;
	fsm::FSMP fsm_up;
	fsm::StringVectorP string_vup;
	fsm::StatementPVectorP statement_vup;
	fsm::StatementP statement_up;
	fsm::StateP state_up;
	fsm::TransitionPVectorP transition_vup;
	const char *str;
	int token;
}

%token <token> CEQ CNE CGE CLE TO
%token <str> ID STRING CONDITION

%type <fsm_vup> Program FSMs 
%type <fsm_up> FSM
%type <string_vup> Args States
%type <statement_vup> Statements
%type <statement_vup> Statement
%type <state_up> Config
%type <transition_vup> Transitions
%type <str> Condition

%start Program

%%

Program 
	: FSMs { mod->root = $1; }
	;

FSMs
	: FSMs FSM { $1->push_back($2); }
	| FSM { FSMPVectorP fsm_ptr(new FSMPVector()); 
			fsm_ptr->push_back($1); $$ = fsm_ptr; }
	;

FSM
	: ID '(' Args ')' ':' Args '{' Statements '}' 
		{
			FSMP fsm(new FSM($1, $3, $6, $8));
			$$ = fsm;
		}
	;

Args
	: Args ',' ID 
		{
			$$->push_back($3);
		}
	| ID {
			StringVectorP svup(new StringVector());
			svup->push_back($1); $$ = svup;
		}
	;

Statements
	: Statements Statement {
		$1->insert($1->end(), $2->begin(), $2->end());
		$$ = $1; 
	}
	| Statement {
		StatementPVectorP svup(new StatementPVector());
		svup->insert(svup->end(), $1->begin(), $1->end());
		$$ = svup;
	}
	;

Statement
	: Config { StatementPVectorP sup(new StatementPVector()); sup->push_back($1); $$ = sup; }
	| Transitions { StatementPVectorP sup(new StatementPVector()); 
					for (auto p : *$1) { sup->push_back(p); } $$ = sup; }
	;

Config
	: ID ':' States { StateP sup(new State($1, $3)); $$ = sup; }
	;

States
	: States ',' ID { $1->push_back($3); $$ = $1; }
	| ID { StringVectorP svup(new StringVector()); svup->push_back($1); $$ = svup; }
	;

Transitions
	: Transitions Condition TO ID { TransitionP tup(new Transition($1->back()->EndState, $4, $2));
		 							$1->push_back(tup); $$ = $1; }
	| ID Condition TO ID { TransitionPVectorP tvup(new TransitionPVector()); 
						   TransitionP tup(new Transition($1, $4, $2));
						   tvup->push_back(tup); $$ = tvup; }
	;

Condition
	: CONDITION { $$ = $1; }
	| %empty    { $$ = ""; }
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
