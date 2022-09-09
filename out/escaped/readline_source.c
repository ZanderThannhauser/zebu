const char* readline_source = ""
	"" "\n"
	"#include <readline/readline.h>" "\n"
	"#include <readline/history.h>" "\n"
	"" "\n"
	"#include <assert.h>" "\n"
	"#include <stdarg.h>" "\n"
	"#include <stdlib.h>" "\n"
	"#include <stdio.h>" "\n"
	"#include <stddef.h>" "\n"
	"#include <string.h>" "\n"
	"" "\n"
	"{{LEXER_TABLE}}" "\n"
	"" "\n"
	"{{LEXER_STARTS_TABLE}}" "\n"
	"" "\n"
	"{{LEXER_ACCEPTS_TABLE}}" "\n"
	"" "\n"
	"{{LEXER_EOF_TABLE}}" "\n"
	"" "\n"
	"{{SHIFT_TABLE}}" "\n"
	"" "\n"
	"{{REDUCE_TABLE}}" "\n"
	"" "\n"
	"{{GOTO_TABLE}}" "\n"
	"" "\n"
	"{{PARSE_TREE_INC_FUNCTIONS}}" "\n"
	"" "\n"
	"{{PARSE_TREE_FREE_FUNCTIONS}}" "\n"
	"" "\n"
	"#define N(array) (sizeof(array) / sizeof(*array))" "\n"
	"" "\n"
	"struct $start* {{PREFIX}}_parse()" "\n"
	"{" "\n"
	"\tstruct { unsigned* data, n, cap; } yacc = {};" "\n"
	"\t" "\n"
	"\tstruct { void** data; unsigned n, cap; } data = {};" "\n"
	"\t" "\n"
	"\tvoid push_state(unsigned state)" "\n"
	"\t{" "\n"
	"\t\tif (yacc.n + 1 >= yacc.cap)" "\n"
	"\t\t{" "\n"
	"\t\t\tyacc.cap = yacc.cap << 1 ?: 1;" "\n"
	"\t\t\tyacc.data = realloc(yacc.data, sizeof(*yacc.data) * yacc.cap);" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\tyacc.data[yacc.n++] = state;" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tvoid push_data(void* element)" "\n"
	"\t{" "\n"
	"\t\tif (data.n + 1 >= data.cap)" "\n"
	"\t\t{" "\n"
	"\t\t\tdata.cap = data.cap << 1 ?: 1;" "\n"
	"\t\t\tdata.data = realloc(data.data, sizeof(*data.data) * data.cap);" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\tdata.data[data.n++] = element;" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tchar* line = readline(\">>> \");" "\n"
	"\t" "\n"
	"\tif (!line) return NULL;" "\n"
	"\t" "\n"
	"\tchar* lexer = line;" "\n"
	"\t" "\n"
	"\tunsigned y, s, r, t;" "\n"
	"\t" "\n"
	"\tvoid* td;" "\n"
	"\t" "\n"
	"\tvoid read_token(unsigned l)" "\n"
	"\t{" "\n"
	"\t\tchar* begin = lexer, *f = NULL;" "\n"
	"\t\t" "\n"
	"\t\tunsigned a, b, c;" "\n"
	"\t\t" "\n"
	"\t\twhile (1)" "\n"
	"\t\t{" "\n"
	"\t\t\tif ((c = *lexer))" "\n"
	"\t\t\t\ta = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\t// it would be cool if it would read another line" "\n"
	"\t\t\t\t// if there wasn\'t an EOF transition" "\n"
	"\t\t\t\ta = l < N({{PREFIX}}_lexer_EOFs) ? {{PREFIX}}_lexer_EOFs[l] : 0;" "\n"
	"\t\t\t}" "\n"
	"\t\t\t" "\n"
	"\t\t\tb = l < N({{PREFIX}}_lexer_accepts) ? {{PREFIX}}_lexer_accepts[l] : 0;" "\n"
	"\t\t\t" "\n"
	"\t\t\tif (a)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tif (b)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tl = a, t = b, f = lexer++;" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tl = a;" "\n"
	"\t\t\t\t\tif (c) lexer++;" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse if (b)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tstruct token* token = malloc(sizeof(*token));" "\n"
	"\t\t\t\ttoken->refcount = 1;" "\n"
	"\t\t\t\ttoken->data = memcpy(malloc(lexer - begin), begin, lexer - begin);" "\n"
	"\t\t\t\ttoken->len = lexer - begin;" "\n"
	"\t\t\t\tt = b, td = token;" "\n"
	"\t\t\t\tbreak;" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse if (t)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tassert(!\"172\" || f);" "\n"
	"\t\t\t\t#if 0" "\n"
	"\t\t\t\tprocess_token(t);" "\n"
	"\t\t\t\tl = {{PREFIX}}_starts[yacc.data[yacc.n - 1]], i = f, t = 0;" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tassert(!\"TODO\");" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\ty = 1, push_state(y);" "\n"
	"\t" "\n"
	"\tread_token({{PREFIX}}_lexer_starts[y]);" "\n"
	"\t" "\n"
	"\tvoid* root;" "\n"
	"\t" "\n"
	"\twhile (yacc.n)" "\n"
	"\t{" "\n"
	"\t\tif (y < N({{PREFIX}}_shifts) && t < N(*{{PREFIX}}_shifts) && (s = {{PREFIX}}_shifts[y][t]))" "\n"
	"\t\t{" "\n"
	"\t\t\ty = s, push_state(y), push_data(td);" "\n"
	"\t\t\tread_token({{PREFIX}}_lexer_starts[y]);" "\n"
	"\t\t}" "\n"
	"\t\telse if (y < N({{PREFIX}}_reduces) && t < N(*{{PREFIX}}_reduces) && (r = {{PREFIX}}_reduces[y][t]))" "\n"
	"\t\t{" "\n"
	"\t\t\tunsigned g;" "\n"
	"\t\t\t" "\n"
	"\t\t\tvoid* d;" "\n"
	"\t\t\t" "\n"
	"\t\t\t{{REDUCTIONRULE_SWITCH}}" "\n"
	"\t\t\t" "\n"
	"\t\t\tif (g == {{START_GRAMMAR_ID}})" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tfree_token(td);" "\n"
	"\t\t\t\tyacc.n = 0, root = d;" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\ty = yacc.data[yacc.n - 1];" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tassert(y < N({{PREFIX}}_gotos) && g < N(*{{PREFIX}}_gotos));" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\ts = {{PREFIX}}_gotos[y][g];" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\ty = s, push_state(y), push_data(d);" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\tassert(!\"190\");" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tassert(!data.n);" "\n"
	"\t" "\n"
	"\tadd_history(line);" "\n"
	"\t" "\n"
	"\tfree(line);" "\n"
	"\t" "\n"
	"\tfree(yacc.data);" "\n"
	"\tfree(data.data);" "\n"
	"\t" "\n"
	"\treturn root;" "\n"
	"}" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"";
