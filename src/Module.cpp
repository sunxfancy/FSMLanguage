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

namespace fsm {

int Module::Parse() {
    yyscan_t sc;
	int res;
	yylex_init(&sc);
	if (this->src) {
		yyset_in(this->src, sc);
		res = yyparse(sc, this);
	} else if (this->buffer) {
		YY_BUFFER_STATE buffer = yy_scan_string(this->buffer, sc);
		res = yyparse(sc, this);
		yy_delete_buffer(buffer, sc);
	} else {
		printf("module error: didn't find input");
		exit(1);
	}
	yylex_destroy(sc);
}

}