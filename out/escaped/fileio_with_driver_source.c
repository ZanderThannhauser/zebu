const char* fileio_with_driver_source = ""
	"" "\n"
	"#define _GNU_SOURCE" "\n"
	"" "\n"
	"#include <limits.h>" "\n"
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
	"\t\tcase \'/\':" "\n"
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
	"\t\tcase \'\\\'\': *out++ = \'\\\\\', *out++ = \'\\\'\', *out = 0; break;" "\n"
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
	"struct zebu_$start* parse(FILE* stream)" "\n"
	"{" "\n"
	"\tvoid* root;" "\n"
	"\tstruct { unsigned* data, n, cap; } yacc = {};" "\n"
	"\tstruct { void** data; unsigned n, cap; } data = {};" "\n"
	"\tstruct { unsigned char* data; unsigned n, cap; unsigned line; } lexer = {" "\n"
	"\t\t.line = 1," "\n"
	"\t};" "\n"
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
	"\tvoid push_char(unsigned char c)" "\n"
	"\t{" "\n"
	"\t\twhile (lexer.n + 1 >= lexer.cap)" "\n"
	"\t\t{" "\n"
	"\t\t\tlexer.cap = lexer.cap << 1 ?: 1;" "\n"
	"\t\t\tlexer.data = realloc(lexer.data, lexer.cap);" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\tlexer.data[lexer.n++] = c;" "\n"
	"\t}" "\n"
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
	"\tunsigned y, t, s, r;" "\n"
	"\tvoid* td;" "\n"
	"\t" "\n"
	"\tvoid read_token(unsigned l)" "\n"
	"\t{" "\n"
	"\t\tunsigned original_l = l, i = 0, a, b, c, f = 0;" "\n"
	"\t\t" "\n"
	"\t\tunsigned line = lexer.line;" "\n"
	"\t\t" "\n"
	"\t\tt = 0;" "\n"
	"\t\t" "\n"
	"\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\tddprintf(\"lexer: \\\"%.*s\\\": l = %u\\n\", lexer.n, lexer.data, l);" "\n"
	"\t\t#endif" "\n"
	"\t\t" "\n"
	"\t\twhile (1)" "\n"
	"\t\t{" "\n"
	"\t\t\tif (i < lexer.n)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tc = lexer.data[i];" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\tchar escaped[10];" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tescape(escaped, c);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tddprintf(\"lexer: c = \'%s\' (0x%X) (from cache)\\n\", escaped, c);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\ta = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse if ((c = getc(stream)) != EOF)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tpush_char(c);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\tchar escaped[10];" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tescape(escaped, c);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tddprintf(\"lexer: c = \'%s\' (0x%X)\\n\", escaped, c);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\ta = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tc = EOF;" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\tddprintf(\"lexer: c = <EOF>\\n\");" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\ta = l < N({{PREFIX}}_lexer_EOFs) ? {{PREFIX}}_lexer_EOFs[l] : 0;" "\n"
	"\t\t\t}" "\n"
	"\t\t\t" "\n"
	"\t\t\tb = l < N({{PREFIX}}_lexer_accepts) ? {{PREFIX}}_lexer_accepts[l] : 0;" "\n"
	"\t\t\t" "\n"
	"\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\tddprintf(\"lexer: \\\"%.*s\\\" (%u): a = %u, b = %u\\n\", lexer.n, lexer.data, i, a, b);" "\n"
	"\t\t\t#endif" "\n"
	"\t\t\t" "\n"
	"\t\t\tif (a)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tif (b)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tl = a, t = b, f = i++, lexer.line = line;" "\n"
	"\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"lexer: l = %u\\n\", l);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tl = a, i++;" "\n"
	"\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"lexer: l = %u\\n\", l);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tif (c == \'\\n\')" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tline++;" "\n"
	"\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"lexer: line: %u\\n\", line);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse if (b)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\tddprintf(\"lexer: token: \\\"%.*s\\\", line: %u\\n\", i, lexer.data, line);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tif (!lexer.n)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"lexer: EOF.\\n\");" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\tt = b, td = NULL;" "\n"
	"\t\t\t\t\tbreak;" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse if (b == 1)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"lexer: whitespace: \\\"%.*s\\\"\\n\", i, lexer.data);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tl = original_l, t = 0, lexer.line = line;" "\n"
	"\t\t\t\t\tmemmove(lexer.data, lexer.data + i, lexer.n - i), lexer.n -= i, i = 0;" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"lexer: i = %u\\n\", i);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tstruct {{PREFIX}}_token* token = malloc(sizeof(*token));" "\n"
	"\t\t\t\t\ttoken->refcount = 1;" "\n"
	"\t\t\t\t\ttoken->line = line;" "\n"
	"\t\t\t\t\ttoken->data = memcpy(malloc(i + 1), lexer.data, i);" "\n"
	"\t\t\t\t\ttoken->data[i] = 0;" "\n"
	"\t\t\t\t\ttoken->len = i;" "\n"
	"\t\t\t\t\tt = b, td = token;" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tlexer.line = line;" "\n"
	"\t\t\t\t\tmemmove(lexer.data, lexer.data + i, lexer.n - i), lexer.n -= i;" "\n"
	"\t\t\t\t\tbreak;" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse if (t)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tif (t == 1)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"lexer: falling back to whitespace: \\\"%.*s\\\"\\n\", f, lexer.data);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tl = original_l, t = 0, line = lexer.line;" "\n"
	"\t\t\t\t\tmemmove(lexer.data, lexer.data + f, lexer.n - f), lexer.n -= f, f = 0, i = 0;" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\t\tddprintf(\"lexer: falling back to token: \\\"%.*s\\\"\\n\", f, lexer.data);" "\n"
	"\t\t\t\t\t#endif" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tstruct {{PREFIX}}_token* token = malloc(sizeof(*token));" "\n"
	"\t\t\t\t\ttoken->refcount = 1;" "\n"
	"\t\t\t\t\ttoken->line = lexer.line;" "\n"
	"\t\t\t\t\ttoken->data = memcpy(malloc(f + 1), lexer.data, f);" "\n"
	"\t\t\t\t\ttoken->data[f] = 0;" "\n"
	"\t\t\t\t\ttoken->len = f;" "\n"
	"\t\t\t\t\ttd = token;" "\n"
	"\t\t\t\t\t" "\n"
	"\t\t\t\t\tmemmove(lexer.data, lexer.data + f, lexer.n - f), lexer.n -= f, f = 0;" "\n"
	"\t\t\t\t\tbreak;" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tif (i != 0)" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tif (c == (unsigned) EOF)" "\n"
	"\t\t\t\t\t\tfprintf(stderr, \"%s: unexpected \'<EOF>\' when reading \'%.*s\' on line %u!\\n\", argv0, i, lexer.data, line);" "\n"
	"\t\t\t\t\telse" "\n"
	"\t\t\t\t\t\tfprintf(stderr, \"%s: unexpected \'%c\' when reading \'%.*s\' on line %u!\\n\", argv0, c, i, lexer.data, line);" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\telse" "\n"
	"\t\t\t\t{" "\n"
	"\t\t\t\t\tif (c == (unsigned) EOF)" "\n"
	"\t\t\t\t\t\tfprintf(stderr, \"%s: unexpected \'<EOF>\' on line %u!\\n\", argv0, line);" "\n"
	"\t\t\t\t\telse" "\n"
	"\t\t\t\t\t\tfprintf(stderr, \"%s: unexpected \'%c\' on line %u!\\n\", argv0, c, line);" "\n"
	"\t\t\t\t}" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\texit(1);" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tpush_state(1), y = 1, read_token(1);" "\n"
	"\t" "\n"
	"\t#ifdef ZEBU_DEBUG" "\n"
	"\tddprintf(\"y = %u, t = %u\\n\", y, t);" "\n"
	"\t#endif" "\n"
	"\t" "\n"
	"\twhile (yacc.n)" "\n"
	"\t{" "\n"
	"\t\tif (y < N({{PREFIX}}_shifts) && t < N(*{{PREFIX}}_shifts) && (s = {{PREFIX}}_shifts[y][t]))" "\n"
	"\t\t{" "\n"
	"\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\tddprintf(\"s == %u\\n\", s);" "\n"
	"\t\t\t#endif" "\n"
	"\t\t\t" "\n"
	"\t\t\ty = s, push_state(y), push_data(td);" "\n"
	"\t\t\t" "\n"
	"\t\t\tread_token({{PREFIX}}_lexer_starts[y]);" "\n"
	"\t\t\t" "\n"
	"\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\tddprintf(\"t = %u\\n\", t);" "\n"
	"\t\t\t#endif" "\n"
	"\t\t}" "\n"
	"\t\telse if (y < N( {{PREFIX}}_reduces) && t < N(*{{PREFIX}}_reduces) && (r = {{PREFIX}}_reduces[y][t]))" "\n"
	"\t\t{" "\n"
	"\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\tddprintf(\"r == %u\\n\", r);" "\n"
	"\t\t\t#endif" "\n"
	"\t\t\t" "\n"
	"\t\t\tunsigned g;" "\n"
	"\t\t\tvoid* d;" "\n"
	"\t\t\t" "\n"
	"\t\t\t{{REDUCTION_RULE_SWITCH}}" "\n"
	"\t\t\t" "\n"
	"\t\t\tif (g == {{START_GRAMMAR_ID}})" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tfree_{{PREFIX}}_token(td);" "\n"
	"\t\t\t\tyacc.n = 0, root = d;" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\ty = yacc.data[yacc.n - 1];" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\tddprintf(\"y = %u\\n\", y);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tassert(y < N({{PREFIX}}_gotos) && g < N(*{{PREFIX}}_gotos));" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\ts = {{PREFIX}}_gotos[y][g];" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\tddprintf(\"s = %u\\n\", s);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\ty = s, push_state(y), push_data(d);" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\tstruct {{PREFIX}}_token* token = td;" "\n"
	"\t\t\t" "\n"
	"\t\t\tfprintf(stderr, \"zebu: unexpected token \'%.*s\'!\\n\", token->len, token->data);" "\n"
	"\t\t\t" "\n"
	"\t\t\texit(1);" "\n"
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
	"\tprint_zebu_$start(NULL, p_root, \"start\", root);" "\n"
	"\t" "\n"
	"\tfree_zebu_$start(root);" "\n"
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
