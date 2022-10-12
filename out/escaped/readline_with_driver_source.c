const char* readline_with_driver_source = ""
	"" "\n"
	"#define _GNU_SOURCE" "\n"
	"" "\n"
	"#include <readline/readline.h>" "\n"
	"#include <readline/history.h>" "\n"
	"" "\n"
	"#include <errno.h>" "\n"
	"#include <limits.h>" "\n"
	"#include <assert.h>" "\n"
	"#include <stdarg.h>" "\n"
	"#include <stdlib.h>" "\n"
	"#include <stdio.h>" "\n"
	"#include <stddef.h>" "\n"
	"#include <string.h>" "\n"
	"" "\n"
	"{{SHIFT_TABLE}}" "\n"
	"" "\n"
	"{{REDUCE_TABLE}}" "\n"
	"" "\n"
	"{{GOTO_TABLE}}" "\n"
	"" "\n"
	"{{LEXER_TRANSITION_TABLE}}" "\n"
	"" "\n"
	"{{LEXER_STARTS_TABLE}}" "\n"
	"" "\n"
	"{{LEXER_ACCEPTS_TABLE}}" "\n"
	"" "\n"
	"{{LEXER_EOF_TABLE}}" "\n"
	"" "\n"
	"{{PARSE_TREE_STRUCTS}}" "\n"
	"" "\n"
	"{{PARSE_TREE_PRINT_TREE_FUNCTIONS}}" "\n"
	"" "\n"
	"{{PARSE_TREE_INC_FUNCTIONS}}" "\n"
	"" "\n"
	"{{PARSE_TREE_FREE_FUNCTIONS}}" "\n"
	"" "\n"
	"#ifdef ZEBU_DEBUG" "\n"
	"{{TOKEN_IDS_TO_SETS}}" "\n"
	"#endif" "\n"
	"" "\n"
	"#define N(array) (sizeof(array) / sizeof(*array))" "\n"
	"" "\n"
	"#ifdef ZEBU_DEBUG" "\n"
	"static void escape(char *out, unsigned char in)" "\n"
	"{" "\n"
	"\tswitch (in)" "\n"
	"\t{" "\n"
	"\t\tcase \' \':" "\n"
	"\t\tcase \'~\':" "\n"
	"\t\tcase \'!\':" "\n"
	"\t\tcase \'@\':" "\n"
	"\t\tcase \'#\':" "\n"
	"\t\tcase \'$\':" "\n"
	"\t\tcase \'%\':" "\n"
	"\t\tcase \'^\':" "\n"
	"\t\tcase \'&\':" "\n"
	"\t\tcase \'*\':" "\n"
	"\t\tcase \'-\':" "\n"
	"\t\tcase \'+\':" "\n"
	"\t\tcase \'=\':" "\n"
	"\t\tcase \'|\':" "\n"
	"\t\tcase \'<\': case \'>\':" "\n"
	"\t\tcase \'(\': case \')\':" "\n"
	"\t\tcase \'{\': case \'}\':" "\n"
	"\t\tcase \'[\': case \']\':" "\n"
	"\t\tcase \':\': case \';\':" "\n"
	"\t\tcase \',\': case \'.\':" "\n"
	"\t\tcase \'_\':" "\n"
	"\t\tcase \'0\' ... \'9\':" "\n"
	"\t\tcase \'a\' ... \'z\':" "\n"
	"\t\tcase \'A\' ... \'Z\':" "\n"
	"\t\t\t*out++ = in;" "\n"
	"\t\t\t*out = 0;" "\n"
	"\t\t\tbreak;" "\n"
	"\t\t" "\n"
	"\t\tcase \'\\\\\': *out++ = \'\\\\\', *out++ = \'\\\\\', *out = 0; break;" "\n"
	"\t\t" "\n"
	"\t\tcase \'\\\"\': *out++ = \'\\\\\', *out++ = \'\\\"\', *out = 0; break;" "\n"
	"\t\t" "\n"
	"\t\tcase \'\\t\': *out++ = \'\\\\\', *out++ = \'t\', *out = 0; break;" "\n"
	"\t\t" "\n"
	"\t\tcase \'\\n\': *out++ = \'\\\\\', *out++ = \'n\', *out = 0; break;" "\n"
	"\t\t" "\n"
	"\t\tdefault:" "\n"
	"\t\t\tsprintf(out, \"\\\\x%02hhX\", in);" "\n"
	"\t\t\tbreak;" "\n"
	"\t}" "\n"
	"}" "\n"
	"#endif" "\n"
	"" "\n"
	"int main(int argc, char** argv)" "\n"
	"{" "\n"
	"\tstruct { unsigned* data, n, cap; } yacc = {};" "\n"
	"\t" "\n"
	"\tstruct { void** data; unsigned n, cap; } data = {};" "\n"
	"\t" "\n"
	"\t#ifdef ZEBU_DEBUG" "\n"
	"\tsetvbuf(stdout, 0, _IONBF, 0);" "\n"
	"\t#endif" "\n"
	"\t" "\n"
	"\t#ifdef ZEBU_DEBUG" "\n"
	"\tvoid ddprintf(const char* fmt, ...)" "\n"
	"\t{" "\n"
	"\t\tfor (unsigned i = 0, n = yacc.n; i < n; i++)" "\n"
	"\t\t\tprintf(\"%u \", yacc.data[i]);" "\n"
	"\t\t" "\n"
	"\t\tprintf(\"| \");" "\n"
	"\t\t" "\n"
	"\t\tva_list va;" "\n"
	"\t\tva_start(va, fmt);" "\n"
	"\t\tvprintf(fmt, va);" "\n"
	"\t\tva_end(va);" "\n"
	"\t}" "\n"
	"\t#endif" "\n"
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
	"\tfor (char* line; (line = readline(\">>> \"));)" "\n"
	"\t{" "\n"
	"\t\tchar* lexer = (void*) line;" "\n"
	"\t\t" "\n"
	"\t\tunsigned y, s, r, t;" "\n"
	"\t\t" "\n"
	"\t\tvoid* td;" "\n"
	"\t\t" "\n"
	"\t\tvoid read_token(unsigned l)" "\n"
	"\t\t{" "\n"
	"\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\tchar escaped[10];" "\n"
	"\t\t\t#endif" "\n"
	"\t\t\t" "\n"
	"\t\t\tunsigned original_l = l;" "\n"
	"\t\t\t" "\n"
	"\t\t\tchar* begin = lexer, *f = NULL;" "\n"
	"\t\t\t" "\n"
	"\t\t\tunsigned a, b;" "\n"
	"\t\t\tunsigned char c;" "\n"
	"\t\t\t" "\n"
	"\t\t\twhile (1)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tif ((c = *lexer))" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\tescape(escaped, c);" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tddprintf(\"lexer: c = \'%s\' (0x%X)\\n\", escaped, c);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\ta = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"lexer: c == <EOF>\\n\");" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\t// it would be cool if it would read another line" "\n"
	"\t\t\t\t\t// if there wasn\'t an EOF transition" "\n"
	"\t\t\t\t\ta = l < N({{PREFIX}}_lexer_EOFs) ? {{PREFIX}}_lexer_EOFs[l] : 0;" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tb = l < N({{PREFIX}}_lexer_accepts) ? {{PREFIX}}_lexer_accepts[l] : 0;" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\tddprintf(\"lexer: l = %u, a = %u, b = %u\\n\", l, a, b);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tif (a)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tif (b)" "\n"
	"\t\t\t\t\t{" "\n"
	"\t\t\t\t\t\tl = a, t = b, f = lexer++;" "\n"
	"\t\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\t\tddprintf(\"lexer: l = %u, t == %u, f = %p (saved)\\n\", l, t, f);" "\n"
	"\t\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t}" "\n"
	"\t\t\t\t\telse" "\n"
	"\t\t\t\t\t{" "\n"
	"\t\t\t\t\t\tl = a;" "\n"
	"\t\t\t\t\t\tif (c) lexer++;" "\n"
	"\t\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\t\tddprintf(\"lexer: l == %u\\n\", l);" "\n"
	"\t\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t}" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse if (b)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"lexer: \\\"%.*s\\\"\\n\", lexer - begin, begin);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tif (b == 1)" "\n"
	"\t\t\t\t\t{" "\n"
	"\t\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\t\tddprintf(\"lexer: whitespace: \\\"%.*s\\\"\\n\", lexer - begin, begin);" "\n"
	"\t\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t\tl = original_l, begin = lexer, f = NULL;" "\n"
	"\t\t\t\t\t}" "\n"
	"\t\t\t\t\telse" "\n"
	"\t\t\t\t\t{" "\n"
	"\t\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\t\tddprintf(\"lexer: token: \\\"%.*s\\\"\\n\", lexer - begin, begin);" "\n"
	"\t\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t\tstruct {{PREFIX}}_token* token = malloc(sizeof(*token));" "\n"
	"\t\t\t\t\t\ttoken->refcount = 1;" "\n"
	"\t\t\t\t\t\ttoken->data = memcpy(malloc(lexer - begin + 1), begin, lexer - begin);" "\n"
	"\t\t\t\t\t\ttoken->len = lexer - begin;" "\n"
	"\t\t\t\t\t\ttoken->data[token->len] = \'\\0\';" "\n"
	"\t\t\t\t\t\tt = b, td = token;" "\n"
	"\t\t\t\t\t\tbreak;" "\n"
	"\t\t\t\t\t}" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse if (f)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tif (t == 1)" "\n"
	"\t\t\t\t\t{" "\n"
	"\t\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\t\tddprintf(\"lexer: falling back to whitespace: \\\"%.*s\\\"\\n\", lexer - begin, begin);" "\n"
	"\t\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t\t" "\n"
	"\t\t\t\t\t\tassert(!\"TODO\");" "\n"
	"\t\t\t\t\t}" "\n"
	"\t\t\t\t\telse" "\n"
	"\t\t\t\t\t{" "\n"
	"\t\t\t\t\t\tlexer = f;" "\n"
	"\t\t\t\t\t\t" "\n"
	"\t\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\t\tddprintf(\"lexer: falling back to token: \\\"%.*s\\\"\\n\", lexer - begin, begin);" "\n"
	"\t\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t\t" "\n"
	"\t\t\t\t\t\tstruct {{PREFIX}}_token* token = malloc(sizeof(*token));" "\n"
	"\t\t\t\t\t\ttoken->refcount = 1;" "\n"
	"\t\t\t\t\t\ttoken->data = memcpy(malloc(lexer - begin + 1), begin, lexer - begin);" "\n"
	"\t\t\t\t\t\ttoken->len = lexer - begin;" "\n"
	"\t\t\t\t\t\ttoken->data[token->len] = \'\\0\';" "\n"
	"\t\t\t\t\t\ttd = token;" "\n"
	"\t\t\t\t\t\tbreak;" "\n"
	"\t\t\t\t\t}" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tassert(!\"TODO\");" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\tyacc.n = 0, data.n = 0, y = 1, push_state(y);" "\n"
	"\t\t" "\n"
	"\t\tread_token({{PREFIX}}_lexer_starts[y]);" "\n"
	"\t\t" "\n"
	"\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\tddprintf(\"y = %u, t == %u (%s)\\n\", y, t, {{PREFIX}}_token_names[t]);" "\n"
	"\t\t#endif" "\n"
	"\t\t" "\n"
	"\t\tvoid* root;" "\n"
	"\t\t" "\n"
	"\t\twhile (yacc.n)" "\n"
	"\t\t{" "\n"
	"\t\t\tif (y < N({{PREFIX}}_shifts) && t < N(*{{PREFIX}}_shifts) && (s = {{PREFIX}}_shifts[y][t]))" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\ty = s, push_state(y), push_data(td);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tread_token({{PREFIX}}_lexer_starts[y]);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\tddprintf(\"t == %u (%s)\\n\", t, {{PREFIX}}_token_names[t]);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse if (y < N({{PREFIX}}_reduces) && t < N(*{{PREFIX}}_reduces) && (r = {{PREFIX}}_reduces[y][t]))" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tunsigned g;" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tvoid* d;" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\tddprintf(\"r = %u\\n\", r);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\t{{REDUCTION_RULE_SWITCH}}" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tif (g == {{START_GRAMMAR_ID}})" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tfree_{{PREFIX}}_token(td);" "\n"
	"\t\t\t\t\tyacc.n = 0, root = d;" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\ty = yacc.data[yacc.n - 1];" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"y = %u\\n\", y);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tassert(y < N({{PREFIX}}_gotos) && g < N(*{{PREFIX}}_gotos));" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\ts = {{PREFIX}}_gotos[y][g];" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"s = %u\\n\", s);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\ty = s, push_state(y), push_data(d);" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tassert(!\"190\");" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\tassert(!data.n);" "\n"
	"\t\t" "\n"
	"\t\tprint_zebu_$start(NULL, p_root, \"start\", root);" "\n"
	"\t\t" "\n"
	"\t\tfree_zebu_$start(root);" "\n"
	"\t\t" "\n"
	"\t\tadd_history(line);" "\n"
	"\t\t" "\n"
	"\t\tfree(line);" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\trl_clear_history();" "\n"
	"\t" "\n"
	"\tfree(yacc.data);" "\n"
	"\t" "\n"
	"\tfree(data.data);" "\n"
	"\t" "\n"
	"\treturn 0;" "\n"
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
