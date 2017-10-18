#include "Module.h"
#include "parser.hpp"
#include "lex.h"

namespace fsm {

int Module::Parse() {
    yyscan_t sc;
	int res;
	yylex_init(&sc);
	if (mod->src) {
		yyset_in(mod->src, sc);
		res = yyparse(sc, mod);
	} else if (mod->buffer) {
		YY_BUFFER_STATE buffer = yy_scan_string(mod->buffer, sc);
		res = yyparse(sc, mod);
		yy_delete_buffer(buffer, sc);
	} else {
		printf("module error: didn't find input");
		exit(1);
	}
	yylex_destroy(sc);
}

}