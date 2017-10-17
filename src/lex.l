%{

#include <cstdio>
#include <cstring>
#include "State.h"
#include "parser.hpp"

#define SAVE_TOKEN yylval.str = maketoken(yytext, yyleng)
#define SAVE_STRING yylval.str = makestring(yytext, yyleng)

extern "C" int yywrap() { return 1; }
char* maketoken(const char* data, int len);
char* makestring(const char* data, int len);

#ifdef _WIN32

/*windows compatibility case*/  
#define YY_NO_UNISTD_H
#include <io.h>  
#define isatty _isatty  
#define fileno _fileno  

#endif

%}

/* show the line number */
%option yylineno
%option reentrant bison-bridge noyywrap

%%

"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/" ; 

#[^\n]*\n				; /* ignore line comment */ 

[ \t\v\f]               ; /* ignore blank token */
\n|\r\n|\r              ; /* ignore line break */

\"(\\.|[^\\"])*\"		SAVE_STRING; return STRING;

"->"                    return TO;

":"						return ':'; 

"("						return '('; 
")"						return ')'; 
"["						return '[';
"]"						return ']';
"{"						return '{'; 
"}"						return '}'; 

"=="                    return CEQ;
"<="                    return CLE;
">="                    return CGE;
"!="                    return CNE;
"<"                     return '<';
">"                     return '>';

"|"                     return '|';
"!"                     return '!';

";"                     return ';';

[a-zA-Z_][a-zA-Z0-9_]*  SAVE_TOKEN; return ID;

%%


char* maketoken(const char* data, int len) {
	char* str = new char[len+1];
	strncpy(str, data, len);
	str[len] = 0;
	return str;
}

char* makestring(const char* data, int len) {
	char* str = new char[len-1];
	strncpy(str, data+1, len-2);
	str[len-2] = 0;
	return str;
}
