const char* piecewise_charbuffer_source = ""
	"" "\n"
	"#include <stdlib.h>" "\n"
	"#include <stddef.h>" "\n"
	"#include <assert.h>" "\n"
	"#include <stdio.h>" "\n"
	"#include <string.h>" "\n"
	"#include <stdarg.h>" "\n"
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
	"#ifdef ZEBU_DEBUG" "\n"
	"{{PARSE_TREE_PRINT_TREE_FUNCTIONS}}" "\n"
	"#endif" "\n"
	"" "\n"
	"{{PARSE_TREE_INC_FUNCTIONS}}" "\n"
	"" "\n"
	"{{PARSE_TREE_FREE_FUNCTIONS}}" "\n"
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
	"\t\t\tsprintf(out, \"\\\\x%02X\", in);" "\n"
	"\t\t\tbreak;" "\n"
	"\t}" "\n"
	"}" "\n"
	"#endif" "\n"
	"" "\n"
	"struct {{PREFIX}}_state" "\n"
	"{" "\n"
	"\tstruct { unsigned* data, n, cap; } y;" "\n"
	"\tstruct { void** data; unsigned n, cap; } d;" "\n"
	"\tstruct { unsigned char* data, n, cap; } l;" "\n"
	"\tunsigned lstate, t, f, i, backup_lstate;" "\n"
	"};" "\n"
	"" "\n"
	"#ifdef ZEBU_DEBUG" "\n"
	"static void ddprintf(struct {{PREFIX}}_state* this, const char* fmt, ...)" "\n"
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
	"#endif" "\n"
	"" "\n"
	"static void push_state(struct {{PREFIX}}_state* this, unsigned ystate)" "\n"
	"{" "\n"
	"\tif (this->y.n == this->y.cap)" "\n"
	"\t{" "\n"
	"\t\tthis->y.cap = this->y.cap << 1 ?: 1;" "\n"
	"\t\tthis->y.data = realloc(this->y.data, sizeof(*this->y.data) * this->y.cap);" "\n"
	"\t\t" "\n"
	"\t\tassert(this->y.data);" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tthis->y.data[this->y.n++] = ystate;" "\n"
	"}" "\n"
	"" "\n"
	"static void push_data(struct {{PREFIX}}_state* this, void* data)" "\n"
	"{" "\n"
	"\tif (this->d.n == this->d.cap)" "\n"
	"\t{" "\n"
	"\t\tthis->d.cap = this->d.cap << 1 ?: 1;" "\n"
	"\t\tthis->d.data = realloc(this->d.data, sizeof(*this->d.data) * this->d.cap);" "\n"
	"\t\t" "\n"
	"\t\tassert(this->d.data);" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tthis->d.data[this->d.n++] = data;" "\n"
	"}" "\n"
	"" "\n"
	"static void append(struct {{PREFIX}}_state* this, unsigned char c)" "\n"
	"{" "\n"
	"\twhile (this->l.n == this->l.cap)" "\n"
	"\t{" "\n"
	"\t\tthis->l.cap = this->l.cap << 1 ?: 1;" "\n"
	"\t\tthis->l.data = realloc(this->l.data, this->l.cap);" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tthis->l.data[this->l.n++] = c;" "\n"
	"}" "\n"
	"" "\n"
	"struct {{PREFIX}}_state* new_{{PREFIX}}_state()" "\n"
	"{" "\n"
	"\tstruct {{PREFIX}}_state* this = malloc(sizeof(*this));" "\n"
	"\t" "\n"
	"\tassert(this);" "\n"
	"\t" "\n"
	"\tthis->y.data = NULL, this->y.n = 0, this->y.cap = 0;" "\n"
	"\tthis->d.data = NULL, this->d.n = 0, this->d.cap = 0;" "\n"
	"\tthis->l.data = NULL, this->l.n = 0, this->l.cap = 0;" "\n"
	"\t" "\n"
	"\tthis->lstate = 1;" "\n"
	"\tthis->backup_lstate = 1;" "\n"
	"\tthis->i = 0;" "\n"
	"\tthis->t = 0;" "\n"
	"\tthis->f = 0;" "\n"
	"\t" "\n"
	"\tpush_state(this, 1);" "\n"
	"\t" "\n"
	"\treturn this;" "\n"
	"}" "\n"
	"" "\n"
	"void {{PREFIX}}_reset(struct {{PREFIX}}_state* this)" "\n"
	"{" "\n"
	"\tthis->y.n = 0, this->y.cap = 0;" "\n"
	"\tthis->d.n = 0, this->d.cap = 0;" "\n"
	"\tthis->l.n = 0, this->l.cap = 0;" "\n"
	"\t" "\n"
	"\tthis->lstate = 1;" "\n"
	"\tthis->backup_lstate = 1;" "\n"
	"\tthis->i = 0;" "\n"
	"\tthis->t = 0;" "\n"
	"\tthis->f = 0;" "\n"
	"\t" "\n"
	"\tpush_state(this, 1);" "\n"
	"}" "\n"
	"" "\n"
	"#define N(array) (sizeof(array) / sizeof(*array))" "\n"
	"" "\n"
	"static void process_token(struct {{PREFIX}}_state* this, unsigned t, void* td)" "\n"
	"{" "\n"
	"\tunsigned s, r, y = this->y.data[this->y.n - 1];" "\n"
	"\t" "\n"
	"\twhile (y < N({{PREFIX}}_reduces) && t < N(*{{PREFIX}}_reduces) && (r = {{PREFIX}}_reduces[y][t]))" "\n"
	"\t{" "\n"
	"\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\tddprintf(this, \"r == %u\\n\", r);" "\n"
	"\t\t#endif" "\n"
	"\t\t" "\n"
	"\t\tunsigned g;" "\n"
	"\t\tvoid* d;" "\n"
	"\t\t" "\n"
	"\t\ttypeof(this->y) yacc = this->y;" "\n"
	"\t\ttypeof(this->d) data = this->d;" "\n"
	"\t\t" "\n"
	"\t\t{{REDUCTIONRULE_SWITCH}}" "\n"
	"\t\t" "\n"
	"\t\tthis->y = yacc;" "\n"
	"\t\tthis->d = data;" "\n"
	"\t\t" "\n"
	"\t\tif (g == {{START_GRAMMAR_ID}})" "\n"
	"\t\t{" "\n"
	"\t\t\tfree_{{PREFIX}}_token(td);" "\n"
	"\t\t\tthis->y.n = 0, this->d.n = 0;" "\n"
	"\t\t\tpush_data(this, d);" "\n"
	"\t\t\treturn;" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\ty = this->y.data[this->y.n - 1];" "\n"
	"\t\t\t" "\n"
	"\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\tddprintf(this, \"y = %u\\n\", y);" "\n"
	"\t\t\t#endif" "\n"
	"\t\t\t" "\n"
	"\t\t\tassert(y < N({{PREFIX}}_gotos) && g < N(*{{PREFIX}}_gotos));" "\n"
	"\t\t\t" "\n"
	"\t\t\ts = {{PREFIX}}_gotos[y][g];" "\n"
	"\t\t\t" "\n"
	"\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\tddprintf(this, \"s = %u\\n\", s);" "\n"
	"\t\t\t#endif" "\n"
	"\t\t\t" "\n"
	"\t\t\ty = s, push_state(this, y), push_data(this, d);" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\ts = y < N({{PREFIX}}_shifts) && t < N(*{{PREFIX}}_shifts) ? {{PREFIX}}_shifts[y][t] : 0;" "\n"
	"\t" "\n"
	"\tif (s)" "\n"
	"\t{" "\n"
	"\t\ty = s, push_state(this, y), push_data(this, td);" "\n"
	"\t}" "\n"
	"\telse" "\n"
	"\t{" "\n"
	"\t\tassert(!\"TODO\");" "\n"
	"\t}" "\n"
	"}" "\n"
	"" "\n"
	"void {{PREFIX}}_parse(struct {{PREFIX}}_state* this," "\n"
	"\tconst unsigned char* buffer," "\n"
	"\tunsigned len)" "\n"
	"{" "\n"
	"\tunsigned l = this->lstate, i = this->i, f = this->f, t = this->t;" "\n"
	"\t" "\n"
	"\tunsigned bl = this->backup_lstate;" "\n"
	"\t" "\n"
	"\tconst unsigned char* end = buffer + len;" "\n"
	"\t" "\n"
	"\t#ifdef ZEBU_DEBUG" "\n"
	"\tchar escaped[10];" "\n"
	"\t#endif" "\n"
	"\t" "\n"
	"\tunsigned char a, b, c;" "\n"
	"\t" "\n"
	"\twhile (buffer < end)" "\n"
	"\t{" "\n"
	"\t\tif (i < this->l.n)" "\n"
	"\t\t{" "\n"
	"\t\t\tc = this->l.data[i];" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\tc = *buffer++;" "\n"
	"\t\t\tappend(this, c);" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\tescape(escaped, c);" "\n"
	"\t\tddprintf(this, \"lexer: c = \'%s\' (0x%X)\\n\", escaped, c);" "\n"
	"\t\t#endif" "\n"
	"\t\t" "\n"
	"\t\ta = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;" "\n"
	"\t\tb = l < N({{PREFIX}}_lexer_accepts) ? {{PREFIX}}_lexer_accepts[l] : 0;" "\n"
	"\t\t" "\n"
	"\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\tddprintf(this, \"lexer: \\\"%.*s\\\" (%u): a = %u, b = %u\\n\", this->l.n, this->l.data, i, a, b);" "\n"
	"\t\t#endif" "\n"
	"\t\t" "\n"
	"\t\tif (a)" "\n"
	"\t\t{" "\n"
	"\t\t\tif (b)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tl = a, t = b, f = i++;" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tl = a, i++;" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t\telse if (b)" "\n"
	"\t\t{" "\n"
	"\t\t\tif (b == 1)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\tddprintf(this, \"lexer: whitespace: \\\"%.*s\\\"\\n\", i, this->l.data);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tmemmove(this->l.data, this->l.data + i, this->l.n - i), this->l.n -= i;" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tl = bl, t = 0, i = 0;" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\tddprintf(this, \"lexer: token: \\\"%.*s\\\"\\n\", i, this->l.data);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tstruct {{PREFIX}}_token* token = malloc(sizeof(*token));" "\n"
	"\t\t\t\ttoken->refcount = 1;" "\n"
	"\t\t\t\ttoken->data = memcpy(malloc(i + 1), this->l.data, i);" "\n"
	"\t\t\t\ttoken->len = i;" "\n"
	"\t\t\t\ttoken->data[i] = 0;" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tprocess_token(this, b, token);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tmemmove(this->l.data, this->l.data + i, this->l.n - i), this->l.n -= i;" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tbl = l = {{PREFIX}}_lexer_starts[this->y.data[this->y.n - 1]], f = 0, t = 0, i = 0;" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t\telse if (t)" "\n"
	"\t\t{" "\n"
	"\t\t\tassert(!\"256\");" "\n"
	"\t\t\t#if 0" "\n"
	"\t\t\tprocess_token(this, t);" "\n"
	"\t\t\tl = {{PREFIX}}_starts[this->y.data[this->y.n - 1]], i = f, t = 0;" "\n"
	"\t\t\t#endif" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\tassert(!\"TODO\");" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tthis->backup_lstate = bl;" "\n"
	"\t" "\n"
	"\tthis->lstate = l, this->i = i, this->f = f, this->t = t;" "\n"
	"}" "\n"
	"" "\n"
	"struct zebu_$start* {{PREFIX}}_close(struct {{PREFIX}}_state* this)" "\n"
	"{" "\n"
	"\tunsigned l = this->lstate, i = this->i, f = this->f, t = this->t;" "\n"
	"\t" "\n"
	"\tunsigned bl = this->backup_lstate;" "\n"
	"\t" "\n"
	"\t#ifdef ZEBU_DEBUG" "\n"
	"\tchar escaped[10];" "\n"
	"\t#endif" "\n"
	"\t" "\n"
	"\tunsigned char a, b, c;" "\n"
	"\t" "\n"
	"\twhile (1)" "\n"
	"\t{" "\n"
	"\t\tif (i < this->l.n)" "\n"
	"\t\t{" "\n"
	"\t\t\tc = this->l.data[i];" "\n"
	"\t\t\t" "\n"
	"\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\tescape(escaped, c);" "\n"
	"\t\t\tddprintf(this, \"lexer: c = \'%s\' (0x%X)\\n\", escaped, c);" "\n"
	"\t\t\t#endif" "\n"
	"\t\t\t" "\n"
	"\t\t\ta = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\tc = EOF;" "\n"
	"\t\t\t" "\n"
	"\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\tddprintf(this, \"lexer: c = <EOF>\\n\");" "\n"
	"\t\t\t#endif" "\n"
	"\t\t\t" "\n"
	"\t\t\ta = l < N({{PREFIX}}_lexer_EOFs) ? {{PREFIX}}_lexer_EOFs[l] : 0;" "\n"
	"\t\t}" "\n"
	"\t\t" "\n"
	"\t\tb = l < N({{PREFIX}}_lexer_accepts) ? {{PREFIX}}_lexer_accepts[l] : 0;" "\n"
	"\t\t" "\n"
	"\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\tddprintf(this, \"lexer: \\\"%.*s\\\" (%u): a = %u, b = %u\\n\", this->l.n, this->l.data, i, a, b);" "\n"
	"\t\t#endif" "\n"
	"\t\t" "\n"
	"\t\tif (a)" "\n"
	"\t\t{" "\n"
	"\t\t\tif (b)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tl = a, t = b, f = i++;" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\tl = a, i++;" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t\telse if (b)" "\n"
	"\t\t{" "\n"
	"\t\t\tif (!this->l.n)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\tddprintf(this, \"lexer: EOF.\\n\");" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\tprocess_token(this, b, NULL);" "\n"
	"\t\t\t\tbreak;" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse if (b == 1)" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\tddprintf(this, \"lexer: whitespace: \\\"%.*s\\\"\\n\", i, this->l.data);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tmemmove(this->l.data, this->l.data + i, this->l.n - i), this->l.n -= i;" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tl = bl, t = 0, i = 0;" "\n"
	"\t\t\t}" "\n"
	"\t\t\telse" "\n"
	"\t\t\t{" "\n"
	"\t\t\t\t#ifdef ZEBU_DEBUG" "\n"
	"\t\t\t\tddprintf(this, \"lexer: token: \\\"%.*s\\\"\\n\", i, this->l.data);" "\n"
	"\t\t\t\t#endif" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tstruct {{PREFIX}}_token* token = malloc(sizeof(*token));" "\n"
	"\t\t\t\ttoken->refcount = 1;" "\n"
	"\t\t\t\ttoken->data = memcpy(malloc(i + 1), this->l.data, i);" "\n"
	"\t\t\t\ttoken->len = i;" "\n"
	"\t\t\t\ttoken->data[i] = 0;" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tprocess_token(this, b, token);" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tmemmove(this->l.data, this->l.data + i, this->l.n - i), this->l.n -= i;" "\n"
	"\t\t\t\t" "\n"
	"\t\t\t\tl = {{PREFIX}}_lexer_starts[this->y.data[this->y.n - 1]], f = 0, t = 0, i = 0;" "\n"
	"\t\t\t}" "\n"
	"\t\t}" "\n"
	"\t\telse if (f)" "\n"
	"\t\t{" "\n"
	"\t\t\tassert(t);" "\n"
	"\t\t\tassert(!\"256\");" "\n"
	"\t\t\t#if 0" "\n"
	"\t\t\tprocess_token(this, t);" "\n"
	"\t\t\tl = {{PREFIX}}_starts[this->y.data[this->y.n - 1]], i = f, t = 0;" "\n"
	"\t\t\t#endif" "\n"
	"\t\t}" "\n"
	"\t\telse" "\n"
	"\t\t{" "\n"
	"\t\t\tassert(!\"TODO\");" "\n"
	"\t\t}" "\n"
	"\t}" "\n"
	"\t" "\n"
	"\tassert(this->d.n == 1);" "\n"
	"\t" "\n"
	"\tstruct zebu_$start* root = this->d.data[0];" "\n"
	"\t" "\n"
	"\t#ifdef ZEBU_DEBUG" "\n"
	"\tprint_{{PREFIX}}_$start(NULL, p_root, \"start\", root);" "\n"
	"\t#endif" "\n"
	"\t" "\n"
	"\treturn root;" "\n"
	"}" "\n"
	"" "\n"
	"void free_{{PREFIX}}_state(struct {{PREFIX}}_state* this)" "\n"
	"{" "\n"
	"\tif (this)" "\n"
	"\t{" "\n"
	"\t\tfree(this->y.data);" "\n"
	"\t\tfree(this->d.data);" "\n"
	"\t\tfree(this->l.data);" "\n"
	"\t\tfree(this);" "\n"
	"\t}" "\n"
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
	"";