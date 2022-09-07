const char* fileio_debug_source = ""
	"" "\n"
	"#define _GNU_SOURCE" "\n"
	"" "\n"
	"#include <stdarg.h>" "\n"
	"#include <string.h>" "\n"
	"#include <unistd.h>" "\n"
	"#include <stdlib.h>" "\n"
	"#include <assert.h>" "\n"
	"#include <stdio.h>" "\n"
	"#include <errno.h>" "\n"
	"" "\n"
	"{{SHIFT_TABLE}}" "\n"
	"" "\n"
	"{{REDUCE_TABLE}}" "\n"
	"" "\n"
	"{{GOTO_TABLE}}" "\n"
	"" "\n"
	"{{LEXER_TABLE}}" "\n"
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
	"#define argv0 (program_invocation_name)" "\n"
	"" "\n"
	"#define N(array) (sizeof(array) / sizeof(*array))" "\n"
	"" "\n"
	"struct cmdln" "\n"
	"{" "\n"
	"\tconst char* input;" "\n"
	"};" "\n"
	"" "\n"
	"void usage(int code)" "\n"
	"{" "\n"
	"\tfprintf(stderr, \"usage: %s <path/to/input/file>\\n\", argv0);" "\n"
	"\texit(code);" "\n"
	"}" "\n"
	"" "\n"
	"struct cmdln* process_cmdln(int argc, char* const* argv)" "\n"
	"{" "\n"
	"\tint opt;" "\n"
	"\t" "\n"
	"\tconst char* input = NULL;" "\n"
	"\t" "\n"
	"\twhile ((opt = getopt(argc, argv, \"h\")) != -1)" "\n"
	"\t{" "\n"
	"\t\tswitch (opt)" "\n"
	"\t\t{" "\n"
	"\t\t\tcase \'h\':" "\n"
	"\t\t\t\tusage(0);" "\n"
	"\t\t\t\tbreak;" "\n"
	"\t\t\t" "\n"
	"\t\t\tdefault:" "\n"
	"\t\t\t\tusage(1);" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tinput = argv[optind++];" "\n"
	"\t" "\n"
	"\tif (!input)" "\n"
	"\t\tusage(1);" "\n"
	"\t" "\n"
	"\tstruct cmdln* retval = malloc(sizeof(*retval));" "\n"
	"\tassert(retval);" "\n"
	"\tretval->input = input;" "\n"
	"\treturn retval;" "\n"
	"}" "\n"
	"" "\n"
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
	"\t\t\tsprintf(out, \"\\\\x%02X\", in);" "\n"
	"\t\t\tbreak;" "\n"
	"\t}" "\n"
	"}" "\n"
	"" "\n"
	"void* parse(FILE* stream)" "\n"
	"{" "\n"
	"\tvoid* root;" "\n"
	"\tstruct { unsigned* data, n, cap; } yacc = {};" "\n"
	"\tstruct { void** data; unsigned n, cap; } data = {};" "\n"
	"\tstruct { unsigned char* data; unsigned n, cap; } lexer = {};" "\n"
	"\t" "\n"
	"\tvoid push_state(unsigned y)" "\n"
	"\t{" "\n"
	"\t\tif (yacc.n + 1 >= yacc.cap)" "\n"
	"\t\t{" "\n"
	"\t\t\tyacc.cap = yacc.cap << 1 ?: 1;" "\n"
	"\t\t\tyacc.data = realloc(yacc.data, sizeof(*yacc.data) * yacc.cap);" "\n"
	"\t\t}" "\n"
	"\t\tyacc.data[yacc.n++] = y;" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tvoid push_data(void* d)" "\n"
	"\t{" "\n"
	"\t\tif (data.n + 1 >= data.cap)" "\n"
	"\t\t{" "\n"
	"\t\t\tdata.cap = data.cap << 1 ?: 1;" "\n"
	"\t\t\tdata.data = realloc(data.data, sizeof(*data.data) * data.cap);" "\n"
	"\t\t}" "\n"
	"\t\tdata.data[data.n++] = d;" "\n"
	"\t}" "\n"
	"\t" "\n"
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
	"\t" "\n"
	"\tunsigned y, t, s, r;" "\n"
	"\tvoid* td;" "\n"
	"\t" "\n"
	"\tvoid read_token(unsigned l)" "\n"
	"\t{" "\n"
	"\t\tvoid append(unsigned char c)" "\n"
	"\t\t{" "\n"
	"\t\t\twhile (lexer.n + 1 >= lexer.cap)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tlexer.cap = lexer.cap << 1 ?: 1;" "\n"
	"\t\t\t\tddprintf(\"lexer.cap == %u\\n\", lexer.cap);" "\n"
	"\t\t\t\tlexer.data = realloc(lexer.data, lexer.cap);" "\n"
	"\t\t\t}" "\n"
	"\t\t\t" "\n"
	"\t\t\tlexer.data[lexer.n++] = c;" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\tunsigned i = 0, a, b, c;" "\n"
	"\t\t" "\n"
	"\t\tt = 0;" "\n"
	"\t\t" "\n"
	"\t\tddprintf(\"l = %u\\n\", l);" "\n"
	"\t\t" "\n"
	"\t\twhile (1)" "\n"
	"\t\t{" "\n"
	"\t\t\tif (i < lexer.n)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tc = lexer.data[i];" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tchar escaped[10];" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tescape(escaped, c);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tprintf(\"c = \'%s\' (0x%X) (from cache)\\n\", escaped, c);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tassert(!\"163\");" "\n"
	"\t\t\t\t#if 0" "\n"
	"\t\t\t\tnext = 0" "\n"
	"\t\t\t\t\t?: (state < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[state][c] : 0)" "\n"
	"\t\t\t\t\t?: (state < N({{PREFIX}}_defaults) ? {{PREFIX}}_defaults[state] : 0);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse if ((c = getc(stream)) != EOF)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tappend(c);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tchar escaped[10];" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tescape(escaped, c);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tddprintf(\"c = \'%s\' (0x%X)\\n\", escaped, c);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\ta = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tc = EOF;" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tddprintf(\"c = <EOF>\\n\");" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\ta = l < N({{PREFIX}}_lexer_EOFs) ? {{PREFIX}}_lexer_EOFs[l] : 0;" "\n"
	"\t\t\t}" "\n"
	"\t\t\t" "\n"
	"\t\t\tb = l < N({{PREFIX}}_lexer_accepts) ? {{PREFIX}}_lexer_accepts[l] : 0;" "\n"
	"\t\t\t" "\n"
	"\t\t\tddprintf(\"a = %u, b = %u\\n\", a, b);" "\n"
	"\t\t\t" "\n"
	"\t\t\tif (a)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tif (b)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tl = a, t = b, f = i++;" "\n"
	"\t\t\t\t\tddprintf(\"l = %u\\n\", l);" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tl = a, i++;" "\n"
	"\t\t\t\t\tddprintf(\"l = %u\\n\", l);" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse if (b)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tif (c != EOF)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tlexer.n--, ungetc(c, stream);" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tddprintf(\"lexer.n == %u\\n\", lexer.n);" "\n"
	"\t\t\t\tddprintf(\"lexer: \\\"%.*s\\\"\\n\", lexer.n, lexer.data);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tappend(\'\\0\');" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tstruct token* token = malloc(sizeof(*token));" "\n"
	"\t\t\t\ttoken->refcount = 1;" "\n"
	"\t\t\t\ttoken->data = memcpy(malloc(lexer.n), lexer.data, lexer.n);" "\n"
	"\t\t\t\tt = b, td = token, lexer.n = 0;" "\n"
	"\t\t\t\tbreak;" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse if (t)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tassert(!\"235\");" "\n"
	"\t\t\t\t#if 0" "\n"
	"\t\t\t\tmemmove(lexer.data, lexer.data + fallback, lexer.n - fallback);" "\n"
	"\t\t\t\tlexer.n -= fallback;" "\n"
	"\t\t\t\treturn token;" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tassert(!\"168\");" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tpush_state(1), y = 1, read_token(1);" "\n"
	"\t" "\n"
	"\tddprintf(\"y = %u, t = %u\\n\", y, t);" "\n"
	"\t" "\n"
	"\twhile (yacc.n)" "\n"
	"\t{" "\n"
	"\t\tif (y < N({{PREFIX}}_shifts) && t < N(*{{PREFIX}}_shifts) && (s = {{PREFIX}}_shifts[y][t]))" "\n"
	"\t\t{" "\n"
	"\t\t\tddprintf(\"s == %u\\n\", s);" "\n"
	"\t\t\t" "\n"
	"\t\t\ty = s, push_state(y), push_data(td);" "\n"
	"\t\t\t" "\n"
	"\t\t\tread_token({{PREFIX}}_lexer_starts[y]);" "\n"
	"\t\t\t" "\n"
	"\t\t\tddprintf(\"t = %u\\n\", t);" "\n"
	"\t\t}" "\n"
	"\t\telse if (y < N( {{PREFIX}}_reduces) && t < N(*{{PREFIX}}_reduces) && (r = {{PREFIX}}_reduces[y][t]))" "\n"
	"\t\t{" "\n"
	"\t\t\tddprintf(\"r == %u\\n\", r);" "\n"
	"\t\t\t" "\n"
	"\t\t\tunsigned g;" "\n"
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
	"\t\t\t\tddprintf(\"y = %u\\n\", y);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tassert(y < N({{PREFIX}}_gotos) && g < N(*{{PREFIX}}_gotos));" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\ts = {{PREFIX}}_gotos[y][g];" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tddprintf(\"s = %u\\n\", s);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\ty = s, push_state(y), push_data(d);" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\tassert(!\"266\");" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tfree(yacc.data);" "\n"
	"\tfree(data.data);" "\n"
	"\tfree(lexer.data);" "\n"
	"\t" "\n"
	"\treturn root;" "\n"
	"}" "\n"
	"" "\n"
	"int main(int argc, char* const* argv)" "\n"
	"{" "\n"
	"\tstruct cmdln* cmdln = process_cmdln(argc, argv);" "\n"
	"\t" "\n"
	"\tFILE* input = fopen(cmdln->input, \"r\");" "\n"
	"\t" "\n"
	"\tif (!input)" "\n"
	"\t{" "\n"
	"\t\tfprintf(stderr, \"%s: fopen(\\\"%s\\\"): %m\\n\", argv0, cmdln->input)," "\n"
	"\t\texit(1);" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tvoid* root = parse(input);" "\n"
	"\t" "\n"
	"\tprint___start___ptree(NULL, p_root, \"start\", root);" "\n"
	"\t" "\n"
	"\tfree___start___ptree(root);" "\n"
	"\t" "\n"
	"\tfclose(input);" "\n"
	"\t" "\n"
	"\tfree(cmdln);" "\n"
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
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"";
