const char* readline_debug_source = ""
	"" "\n"
	"#include <assert.h>" "\n"
	"#include <stdarg.h>" "\n"
	"#include <stdlib.h>" "\n"
	"#include <stdio.h>" "\n"
	"#include <stdio.h>" "\n"
	"#include <readline/readline.h>" "\n"
	"#include <readline/history.h>" "\n"
	"#include <stdlib.h>" "\n"
	"#include <stddef.h>" "\n"
	"#include <assert.h>" "\n"
	"#include <stdio.h>" "\n"
	"#include <string.h>" "\n"
	"#include <stdarg.h>" "\n"
	"" "\n"
	"struct <PREFIX>_state" "\n"
	"{" "\n"
	"\tstruct { unsigned* data, n, cap; } y;" "\n"
	"\tstruct { unsigned char* data, n, cap; } l;" "\n"
	"\tunsigned lstate, t;" "\n"
	"};" "\n"
	"" "\n"
	"static void ddprintf(struct zebu_state* this, const char* fmt, ...)" "\n"
	"{" "\n"
	"\tfor (unsigned i = 0, n = this->y.n; i < n; i++)" "\n"
	"\t\tprintf(\"%u \", this->y.data[i]);" "\n"
	"\t" "\n"
	"\tprintf(\"| \");" "\n"
	"\t" "\n"
	"\tva_list va;" "\n"
	"\tva_start(va, fmt);" "\n"
	"\tvprintf(fmt, va);" "\n"
	"\tva_end(va);" "\n"
	"}" "\n"
	"" "\n"
	"static void push(struct <PREFIX>_state* this, unsigned ystate)" "\n"
	"{" "\n"
	"\tif (this->y.n + 1 >= this->y.cap)" "\n"
	"\t{" "\n"
	"\t\tthis->y.cap = this->y.cap << 1 ?: 1;" "\n"
	"\t\tthis->y.data = realloc(this->y.data, sizeof(*this->y.data) * this->y.cap);" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tthis->y.data[this->y.n++] = ystate;" "\n"
	"}" "\n"
	"" "\n"
	"static void append(struct <PREFIX>_state* this, const unsigned char* text, size_t length)" "\n"
	"{" "\n"
	"\twhile (this->l.n + length >= this->l.cap)" "\n"
	"\t{" "\n"
	"\t\tthis->l.cap = this->l.cap << 1 ?: 1;" "\n"
	"\t\tthis->l.data = realloc(this->l.data, this->l.cap);" "\n"
	"\t}" "\n"
	"\tmemcpy(this->l.data + this->l.n, text, length);" "\n"
	"\tthis->l.n += length;" "\n"
	"}" "\n"
	"" "\n"
	"static struct <PREFIX>_state* new_<PREFIX>_state()" "\n"
	"{" "\n"
	"\tstruct <PREFIX>_state* this = malloc(sizeof(*this));" "\n"
	"\tassert(this);" "\n"
	"\tthis->y.data = NULL, this->y.n = 0, this->y.cap = 0;" "\n"
	"\tthis->l.data = NULL, this->l.n = 0, this->l.cap = 0;" "\n"
	"\tthis->lstate = 1, this->t = 0;" "\n"
	"\tpush(this, 1);" "\n"
	"\treturn this;" "\n"
	"}" "\n"
	"" "\n"
	"static void <PREFIX>_reset(struct <PREFIX>_state* this)" "\n"
	"{" "\n"
	"\tthis->y.n = 0;" "\n"
	"\tthis->l.n = 0;" "\n"
	"\tthis->lstate = 1;" "\n"
	"\tpush(this, 1);" "\n"
	"\tddprintf(this, \"y = %u, l == %u\\n\", 1, 1);" "\n"
	"}" "\n"
	"" "\n"
	"#define N(array) (sizeof(array) / sizeof(*array))" "\n"
	"" "\n"
	"static void process_token(struct <PREFIX>_state* this, unsigned t)" "\n"
	"{" "\n"
	"\tunsigned b, d, p, y = this->y.data[this->y.n - 1];" "\n"
	"\t" "\n"
	"\twhile (!(y < N(<PREFIX>_shifts) && t < N(*<PREFIX>_shifts) && (b = <PREFIX>_shifts[y][t])))" "\n"
	"\t{" "\n"
	"\t\tif (y < N(<PREFIX>_reduces) && t < N(*<PREFIX>_reduces) && (b = <PREFIX>_reduces[y][t]))" "\n"
	"\t\t{" "\n"
	"\t\t\tddprintf(this, \"b == %u\\n\", b);" "\n"
	"\t\t\tddprintf(this, \"g == \\\"%s\\\"\\n\", zebu_grammar_names[b]);" "\n"
	"\t\t\t" "\n"
	"\t\t\tif (b == start_grammar_id)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tthis->y.n = 0;" "\n"
	"\t\t\t\treturn;" "\n"
	"\t\t\t}" "\n"
	"\t\t\t" "\n"
	"\t\t\tddprintf(this, \"p == %u\\n\", p = zebu_popcounts[y][t]);" "\n"
	"\t\t\t" "\n"
	"\t\t\tthis->y.n -= p;" "\n"
	"\t\t\t" "\n"
	"\t\t\ty = this->y.data[this->y.n - 1];" "\n"
	"\t\t\tddprintf(this, \"y = %u\\n\", y);" "\n"
	"\t\t\t" "\n"
	"\t\t\tassert(y < N(<PREFIX>_shifts) && b < N(*<PREFIX>_shifts));" "\n"
	"\t\t\t" "\n"
	"\t\t\td = <PREFIX>_shifts[y][b];" "\n"
	"\t\t\tddprintf(this, \"d = %u\\n\", d);" "\n"
	"\t\t\t" "\n"
	"\t\t\tpush(this, d), y = d;" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\tassert(!\"TODO\");" "\n"
	"\t\t\texit(1);" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tpush(this, b), y = b;" "\n"
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
	"\t\tcase \'(\':" "\n"
	"\t\tcase \')\':" "\n"
	"\t\tcase \'-\':" "\n"
	"\t\tcase \'+\':" "\n"
	"\t\tcase \'=\':" "\n"
	"\t\tcase \'|\':" "\n"
	"\t\tcase \'{\': case \'}\':" "\n"
	"\t\tcase \'[\': case \']\':" "\n"
	"\t\tcase \':\': case \';\':" "\n"
	"\t\tcase \',\': case \'.\':" "\n"
	"\t\tcase \'0\' ... \'9\':" "\n"
	"\t\tcase \'a\' ... \'z\':" "\n"
	"\t\tcase \'A\' ... \'Z\':" "\n"
	"\t\t\t*out++ = in;" "\n"
	"\t\t\t*out = 0;" "\n"
	"\t\t\tbreak;" "\n"
	"\t\t" "\n"
	"\t\tdefault:" "\n"
	"\t\t\tsprintf(out, \"\\\\x%02X\", in);" "\n"
	"\t\t\tbreak;" "\n"
	"\t}" "\n"
	"}" "\n"
	"" "\n"
	"static void <PREFIX>_parse(struct <PREFIX>_state* this, const unsigned char* text, size_t length)" "\n"
	"{" "\n"
	"\tunsigned c, l = this->lstate;" "\n"
	"\tunsigned a, b, i, n, f, t = this->t;" "\n"
	"\t" "\n"
	"\tchar escaped[10];" "\n"
	"\t" "\n"
	"\ti = this->l.n;" "\n"
	"\t" "\n"
	"\tappend(this, text, length);" "\n"
	"\t" "\n"
	"\tfor (n = this->l.n, f = 0; i < n;)" "\n"
	"\t{" "\n"
	"\t\tc = this->l.data[i];" "\n"
	"\t\t" "\n"
	"\t\tescape(escaped, c);" "\n"
	"\t\t" "\n"
	"\t\tddprintf(this, \"c = %s (0x%X)\\n\", escaped, c);" "\n"
	"\t\t" "\n"
	"\t\ta = (c < N(*<PREFIX>_lexer) ? <PREFIX>_lexer[l][c] : 0) ?: (l < N( <PREFIX>_defaults) ? <PREFIX>_defaults[l] : 0);" "\n"
	"\t\tb = (l < N(<PREFIX>_accepts) ? <PREFIX>_accepts[l] : 0);" "\n"
	"\t\t" "\n"
	"\t\tif (a)" "\n"
	"\t\t{" "\n"
	"\t\t\tif (b)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tl = a, t = b, f = i++;" "\n"
	"\t\t\t\tddprintf(this, \"l = %u, t == %u, f = %u (saved)\\n\", l, t, f);" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tl = a, i++;" "\n"
	"\t\t\t\tddprintf(this, \"l == %u\\n\", l);" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t\telse if (b)" "\n"
	"\t\t{" "\n"
	"\t\t\tprocess_token(this, b);" "\n"
	"\t\t\tl = <PREFIX>_starts[this->y.data[this->y.n - 1]], f = i, t = 0;" "\n"
	"\t\t\tddprintf(this, \"l == %u, f = %u, t = %u\\n\", l, f, t);" "\n"
	"\t\t}" "\n"
	"\t\telse if (t)" "\n"
	"\t\t{" "\n"
	"\t\t\tprocess_token(this, t);" "\n"
	"\t\t\tl = <PREFIX>_starts[this->y.data[this->y.n - 1]], i = f, t = 0;" "\n"
	"\t\t\tddprintf(this, \"l == %u, i = %u, t = %u\\n\", l, i, t);" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\tassert(!\"TODO\");" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tmemcpy(this->l.data, this->l.data + f, this->l.n = n - f);" "\n"
	"\t" "\n"
	"\tthis->t = t;" "\n"
	"\t" "\n"
	"\tthis->lstate = l;" "\n"
	"}" "\n"
	"" "\n"
	"static void <PREFIX>_parse_EOF(struct <PREFIX>_state* this)" "\n"
	"{" "\n"
	"\tunsigned i = this->l.n, n = i, l = this->lstate;" "\n"
	"\tunsigned a, b, c, f = 0, t = this->t;" "\n"
	"\t" "\n"
	"\tchar escaped[10];" "\n"
	"\t" "\n"
	"\twhile (1)" "\n"
	"\t{" "\n"
	"\t\tassert(i <= n + 1);" "\n"
	"\t\t" "\n"
	"\t\tif (i < n)" "\n"
	"\t\t{" "\n"
	"\t\t\tc = this->l.data[i];" "\n"
	"\t\t\t" "\n"
	"\t\t\tescape(escaped, c);" "\n"
	"\t\t\t" "\n"
	"\t\t\tddprintf(this, \"c = %s (0x%X)\\n\", escaped, c);" "\n"
	"\t\t" "\n"
	"\t\t\ta = (c < N(*<PREFIX>_lexer) ? <PREFIX>_lexer[l][c] : 0) ?: (l < N( <PREFIX>_defaults) ? <PREFIX>_defaults[l] : 0);" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\tddprintf(this, \"c == <EOF>\\n\");" "\n"
	"\t\t\ta = l < N(<PREFIX>_EOFs) ? <PREFIX>_EOFs[l] : 0;" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\tb = (l < N(<PREFIX>_accepts) ? <PREFIX>_accepts[l] : 0);" "\n"
	"\t\t" "\n"
	"\t\tif (a)" "\n"
	"\t\t{" "\n"
	"\t\t\tif (b)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tl = a, t = b, f = i++;" "\n"
	"\t\t\t\tddprintf(this, \"l = %u, t == %u, f = %u (saved)\\n\", l, t, f);" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tl = a, i++;" "\n"
	"\t\t\t\tddprintf(this, \"l == %u\\n\", l);" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t\telse if (b)" "\n"
	"\t\t{" "\n"
	"\t\t\tprocess_token(this, b);" "\n"
	"\t\t\t" "\n"
	"\t\t\tif (!this->y.n) break;" "\n"
	"\t\t\t" "\n"
	"\t\t\tl = <PREFIX>_starts[this->y.data[this->y.n - 1]], f = i, t = 0;" "\n"
	"\t\t\tddprintf(this, \"l == %u, f = %u, t = %u\\n\", l, f, t);" "\n"
	"\t\t}" "\n"
	"\t\telse if (t)" "\n"
	"\t\t{" "\n"
	"\t\t\tprocess_token(this, t);" "\n"
	"\t\t\tl = <PREFIX>_starts[this->y.data[this->y.n - 1]], i = f, t = 0;" "\n"
	"\t\t\tddprintf(this, \"l == %u, i = %u, t = %u\\n\", l, i, t);" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\tassert(!\"TODO\");" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"}" "\n"
	"" "\n"
	"static void free_<PREFIX>_state(struct <PREFIX>_state* this)" "\n"
	"{" "\n"
	"\tfree(this->y.data);" "\n"
	"\tfree(this->l.data);" "\n"
	"\tfree(this);" "\n"
	"}" "\n"
	"" "\n"
	"int main()" "\n"
	"{" "\n"
	"\tstruct zebu_state* new = new_zebu_state();" "\n"
	"\t" "\n"
	"\tfor (char* line; (line = readline(\">>> \"));)" "\n"
	"\t{" "\n"
	"\t\tzebu_reset(new);" "\n"
	"\t\t" "\n"
	"\t\tzebu_parse(new, (unsigned char*) line, strlen(line));" "\n"
	"\t\t" "\n"
	"\t\tzebu_parse_EOF(new);" "\n"
	"\t\t" "\n"
	"\t\tputs(\"accepted!\");" "\n"
	"\t\t" "\n"
	"\t\tadd_history(line);" "\n"
	"\t\t" "\n"
	"\t\tfree(line);" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tfree_zebu_state(new);" "\n"
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
