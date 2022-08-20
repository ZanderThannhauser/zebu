const char* fileio_passfail_source = ""
	"" "\n"
	"#define _GNU_SOURCE" "\n"
	"" "\n"
	"#include <string.h>" "\n"
	"#include <unistd.h>" "\n"
	"#include <stdlib.h>" "\n"
	"#include <assert.h>" "\n"
	"#include <stdio.h>" "\n"
	"#include <errno.h>" "\n"
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
	"struct lexer { unsigned char* data; unsigned n, cap; };" "\n"
	"" "\n"
	"unsigned read_token(struct lexer* lexer, FILE* stream, unsigned state)" "\n"
	"{" "\n"
	"\tvoid append(unsigned char c)" "\n"
	"\t{" "\n"
	"\t\twhile (lexer->n + 1 >= lexer->cap)" "\n"
	"\t\t{" "\n"
	"\t\t\tlexer->cap = lexer->cap << 1 ?: 1;" "\n"
	"\t\t\tlexer->data = realloc(lexer->data, lexer->cap);" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\tlexer->data[lexer->n++] = c;" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tunsigned i = 0;" "\n"
	"\t" "\n"
	"\tunsigned token = 0, fallback;" "\n"
	"\t" "\n"
	"\twhile (1)" "\n"
	"\t{" "\n"
	"\t\tunsigned next, accept, c;" "\n"
	"\t\t" "\n"
	"\t\tif (i < lexer->n)" "\n"
	"\t\t{" "\n"
	"\t\t\tc = lexer->data[i];" "\n"
	"\t\t\t" "\n"
	"\t\t\tnext = 0" "\n"
	"\t\t\t\t?: (c < N(*<PREFIX>_lexer) ? <PREFIX>_lexer[state][c] : 0)" "\n"
	"\t\t\t\t?: (state < N( <PREFIX>_defaults) ? <PREFIX>_defaults[state] : 0);" "\n"
	"\t\t}" "\n"
	"\t\telse if ((c = getc(stream)) != EOF)" "\n"
	"\t\t{" "\n"
	"\t\t\tappend(c);" "\n"
	"\t\t\t" "\n"
	"\t\t\tnext = 0" "\n"
	"\t\t\t\t?: (c < N(*<PREFIX>_lexer) ? <PREFIX>_lexer[state][c] : 0)" "\n"
	"\t\t\t\t?: (state < N( <PREFIX>_defaults) ? <PREFIX>_defaults[state] : 0);" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\tc = EOF;" "\n"
	"\t\t\tnext = state < N(<PREFIX>_EOFs) ? <PREFIX>_EOFs[state] : 0;" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\taccept = (state < N(<PREFIX>_accepts) ? <PREFIX>_accepts[state] : 0);" "\n"
	"\t\t" "\n"
	"\t\tif (next)" "\n"
	"\t\t{" "\n"
	"\t\t\tif (accept)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tstate = next, token = accept, fallback = i++;" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tstate = next, i++;" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t\telse if (accept)" "\n"
	"\t\t{" "\n"
	"\t\t\tlexer->n = 0;" "\n"
	"\t\t\tif (c != EOF) lexer->data[lexer->n++] = c;" "\n"
	"\t\t\treturn accept;" "\n"
	"\t\t}" "\n"
	"\t\telse if (token)" "\n"
	"\t\t{" "\n"
	"\t\t\tmemmove(lexer->data, lexer->data + fallback, lexer->n - fallback);" "\n"
	"\t\t\tlexer->n -= fallback;" "\n"
	"\t\t\treturn token;" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\tassert(!\"168\");" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"}" "\n"
	"" "\n"
	"void parse(FILE* stream)" "\n"
	"{" "\n"
	"\tstruct { unsigned* data, n, cap; } stack = {};" "\n"
	"\tstruct lexer lexer = {};" "\n"
	"\t" "\n"
	"\tvoid push(unsigned y)" "\n"
	"\t{" "\n"
	"\t\tif (stack.n + 1 >= stack.cap)" "\n"
	"\t\t{" "\n"
	"\t\t\tstack.cap = stack.cap << 1 ?: 1;" "\n"
	"\t\t\tstack.data = realloc(stack.data, sizeof(*stack.data) * stack.cap);" "\n"
	"\t\t}" "\n"
	"\t\tstack.data[stack.n++] = y;" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tpush(1);" "\n"
	"\t" "\n"
	"\tunsigned g = 0, t = read_token(&lexer, stream, 1);" "\n"
	"\t" "\n"
	"\twhile (stack.n)" "\n"
	"\t{" "\n"
	"\t\tunsigned y = stack.data[stack.n - 1], s, r;" "\n"
	"\t\t" "\n"
	"\t\tif (y < N(<PREFIX>_shifts) && t < N(*<PREFIX>_shifts) && (s = <PREFIX>_shifts[y][g ?: t]))" "\n"
	"\t\t{" "\n"
	"\t\t\tpush(s);" "\n"
	"\t\t\tif (g) g = 0;" "\n"
	"\t\t\telse t = read_token(&lexer, stream, <PREFIX>_starts[s]);" "\n"
	"\t\t}" "\n"
	"\t\telse if (y < N(<PREFIX>_reduces) && t < N(*<PREFIX>_reduces) && (r = <PREFIX>_reduces[y][t]))" "\n"
	"\t\t{" "\n"
	"\t\t\tif (r == start_grammar_id)" "\n"
	"\t\t\t\tstack.n = 0;" "\n"
	"\t\t\telse" "\n"
	"\t\t\t\tstack.n -= <PREFIX>_popcounts[y][t], g = r;" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\tassert(!\"266\");" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tfree(stack.data);" "\n"
	"\tfree(lexer.data);" "\n"
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
	"\tparse(input);" "\n"
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
