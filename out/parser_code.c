
#include "parser_code.h"

const char parser_code[] = ""

	"#include <stdlib.h>" "\n"
	"#include <stddef.h>" "\n"
	"#include <assert.h>" "\n"
	
	"struct <PREFIX>_state { unsigned* data, n, cap, lstate; };" "\n"
	
	"static void push(struct <PREFIX>_state* this, unsigned ystate) {" "\n"
	"\t""if (this->n + 1 >= this->cap) {" "\n"
	"\t""\t""this->cap = this->cap << 1 ?: 1;" "\n"
	"\t""\t""this->data = realloc(this->data, sizeof(*this->data) * this->cap);" "\n"
	"\t""}" "\n"
	"\t""this->data[this->n++] = ystate;" "\n"
	"}" "\n"
	
	"struct <PREFIX>_state* new_<PREFIX>_state() {" "\n"
	"\t""struct <PREFIX>_state* this = malloc(sizeof(*this));" "\n"
	"\t""assert(this);" "\n"
	"\t""this->data = NULL, this->n = 0, this->cap = 0;" "\n"
	"\t""this->lstate = 1;" "\n"
	"\t""push(this, 1);" "\n"
	"\t""return this;" "\n"
	"}" "\n"
	
	"void <PREFIX>_reset(struct <PREFIX>_state* this) {" "\n"
	"\t""this->n = 0;" "\n"
	"\t""this->lstate = 1;" "\n"
	"\t""push(this, 1);" "\n"
	"}" "\n"
	
	"#define N(array) (sizeof(array) / sizeof(*array))" "\n"
	
	"static void process_token(struct <PREFIX>_state* this, unsigned t) {" "\n"
	"\t""unsigned b, d, y = this->data[this->n - 1];" "\n"
	"\t""while (!(y < N(<PREFIX>_shifts) && t < N(*<PREFIX>_shifts) && (b = <PREFIX>_shifts[y][t]))) {" "\n"
	"\t""\t""if (y < N(<PREFIX>_reduces) && t < N(*<PREFIX>_reduces) && (b = <PREFIX>_reduces[y][t])) {" "\n"
	"\t""\t""\t""unsigned s = t;" "\n"
	"\t""\t""\t""while (!(1" "\n"
	"\t""\t""\t""\t"" && y < N(<PREFIX>_shifts) && b < N(*<PREFIX>_shifts) && (d = <PREFIX>_shifts[y][b])" "\n"
	"\t""\t""\t""\t"" && b < N(<PREFIX>_firsts) && s < N(*<PREFIX>_firsts) && (    <PREFIX>_firsts[b][s])) {" "\n"
	"\t""\t""\t""\t""if (this->n == 1) return;" "\n"
	"\t""\t""\t""\t""s = this->data[--this->n - 1];" "\n"
	"\t""\t""\t""\t""y = this->data[--this->n - 1];" "\n"
	"\t""\t""\t""}" "\n"
	"\t""\t""\t""push(this, b), push(this, d), y = d;" "\n"
	"\t""\t""} else {" "\n"
	"\t""\t""\t""assert(!\"TODO\");" "\n"
	"\t""\t""\t""exit(1);" "\n"
	"\t""\t""}" "\n"
	"\t""}" "\n"
	"\t""push(this, t), push(this, b), y = b;" "\n"
	"}" "\n"
	
	"void <PREFIX>_parse(struct <PREFIX>_state* this, const unsigned char* text, size_t length) {" "\n"
	"\t""unsigned a, b, c, l = this->lstate;" "\n"
	"\t""while (c = *text++, length--) {" "\n"
	"\t""\t""while (!(a = c < N(*<PREFIX>_lexer) ? <PREFIX>_lexer[l][c] : l < N(<PREFIX>_defaults) ? <PREFIX>_defaults[l] : 0)) {" "\n"
	"\t""\t""\t""if (l < N(<PREFIX>_accepts) && (b = <PREFIX>_accepts[l])) {" "\n"
	"\t""\t""\t""\t""process_token(this, b);" "\n"
	"\t""\t""\t""\t""l = <PREFIX>_starts[this->data[this->n - 1]];" "\n"
	"\t""\t""\t""} else {" "\n"
	"\t""\t""\t""\t""assert(!\"TODO\");" "\n"
	"\t""\t""\t""\t""exit(1);" "\n"
	"\t""\t""\t""}" "\n"
	"\t""\t""}" "\n"
	"\t""\t""l = a;" "\n"
	"\t""}" "\n"
	"\t""this->lstate = l;" "\n"
	"}" "\n"
	
	"void <PREFIX>_parse_EOF(struct <PREFIX>_state* this) {" "\n"
	"\t""unsigned b, l = this->lstate;" "\n"
	"\t""if (l < N(<PREFIX>_accepts) && (b = <PREFIX>_accepts[l])) {" "\n"
	"\t""\t""process_token(this, b);" "\n"
	"\t""} else {" "\n"
	"\t""\t""assert(!\"TODO\");" "\n"
	"\t""\t""exit(1);" "\n"
	"\t""}" "\n"
	"\t""process_token(this, 1);" "\n"
	"}" "\n"
	
	"void free_<PREFIX>_state(struct <PREFIX>_state* this) {" "\n"
	"\t""free(this->data);" "\n"
	"\t""free(this);" "\n"
	"}" "\n"

"";

const char parser_debug[] = ""

	"#include <stdlib.h>" "\n"
	"#include <stddef.h>" "\n"
	"#include <assert.h>" "\n"
	"#include <stdio.h>" "\n"
	"#include <stdarg.h>" "\n"
	
	"struct <PREFIX>_state { unsigned* data, n, cap, lstate; };" "\n"
	
	"static void push(struct <PREFIX>_state* this, unsigned ystate) {" "\n"
	"\t""if (this->n + 1 >= this->cap) {" "\n"
	"\t""\t""this->cap = this->cap << 1 ?: 1;" "\n"
	"\t""\t""this->data = realloc(this->data, sizeof(*this->data) * this->cap);" "\n"
	"\t""}" "\n"
	"\t""this->data[this->n++] = ystate;" "\n"
	"}" "\n"
	
	"static void ddprintf(struct zebu_state* this, const char* fmt, ...) {" "\n"
	"\t""for (unsigned i = 0, n = this->n; i < n; i++) " "\n"
	"\t""\t""printf(\"%u \", this->data[i]);" "\n"
	"\t""printf(\"| \");" "\n"
	"\t""va_list va;" "\n"
	"\t""va_start(va, fmt);" "\n"
	"\t""vprintf(fmt, va);" "\n"
	"\t""va_end(va);" "\n"
	"}" "\n"

	"struct <PREFIX>_state* new_<PREFIX>_state() {" "\n"
	"\t""struct <PREFIX>_state* this = malloc(sizeof(*this));" "\n"
	"\t""assert(this);" "\n"
	"\t""this->data = NULL, this->n = 0, this->cap = 0;" "\n"
	"\t""this->lstate = 1;" "\n"
	"\t""push(this, 1);" "\n"
	"\t""return this;" "\n"
	"}" "\n"
	
	"void <PREFIX>_reset(struct <PREFIX>_state* this) {" "\n"
	"\t""this->n = 0;" "\n"
	"\t""this->lstate = 1;" "\n"
	"\t""push(this, 1);" "\n"
	"}" "\n"
	
	"#define N(array) (sizeof(array) / sizeof(*array))" "\n"
	
	"static void process_token(struct <PREFIX>_state* this, unsigned t) {" "\n"
	"\t""ddprintf(this, \"t == %u\\n\", t);" "\n"
	"\t""unsigned b, d, y = this->data[this->n - 1];" "\n"
	"\t""while (!(y < N(<PREFIX>_shifts) && t < N(*<PREFIX>_shifts) && (b = <PREFIX>_shifts[y][t]))) {" "\n"
	"\t""\t""if (y < N(<PREFIX>_reduces) && t < N(*<PREFIX>_reduces) && (b = <PREFIX>_reduces[y][t])) {" "\n"
	"\t""\t""ddprintf(this, \"b == %u\\n\", b);" "\n"
	"\t""\t""ddprintf(this, \"g == \\\"%s\\\"\\n\", <PREFIX>_grammar_names[b]);" "\n"
	"\t""\t""\t""unsigned s = t;" "\n"
	"\t""\t""\t""while (!(1" "\n"
	"\t""\t""\t""\t"" && y < N(<PREFIX>_shifts) && b < N(*<PREFIX>_shifts) && (d = <PREFIX>_shifts[y][b])" "\n"
	"\t""\t""\t""\t"" && b < N(<PREFIX>_firsts) && s < N(*<PREFIX>_firsts) && (    <PREFIX>_firsts[b][s]))) {" "\n"
	"\t""\t""\t""\t""if (this->n == 1) return;" "\n"
	"\t""\t""\t""\t""s = this->data[--this->n - 1];" "\n"
	"\t""\t""\t""\t""y = this->data[--this->n - 1];" "\n"
	"\t""\t""\t""\t""ddprintf(this, \"y == %u\\n\", y);" "\n"
	"\t""\t""\t""}" "\n"
	"\t""\t""\t""push(this, b), push(this, d), y = d;" "\n"
	"\t""\t""\t""ddprintf(this, \"y == %u\\n\", y);" "\n"
	"\t""\t""} else {" "\n"
	"\t""\t""\t""assert(!\"TODO\");" "\n"
	"\t""\t""\t""exit(1);" "\n"
	"\t""\t""}" "\n"
	"\t""}" "\n"
	"\t""push(this, t), push(this, b), y = b;" "\n"
	"}" "\n"
	
	"void <PREFIX>_parse(struct <PREFIX>_state* this, const unsigned char* text, size_t length) {" "\n"
	"\t""unsigned a, b, c, l = this->lstate;" "\n"
	"\t""while (c = *text++, length--) {" "\n"
	"\t""\t""ddprintf(this, \"c == %c\\n\", c);" "\n"
	"\t""\t""while (!(a = 0" "\n"
	"\t""\t""\t""\t""?: (c < N(*<PREFIX>_lexer)    ? <PREFIX>_lexer[l][c] : 0)" "\n"
	"\t""\t""\t""\t""?: (l < N( <PREFIX>_defaults) ? <PREFIX>_defaults[l] : 0))) {" "\n"
	"\t""\t""\t""if (l < N(<PREFIX>_accepts) && (b = <PREFIX>_accepts[l])) {" "\n"
	"\t""\t""\t""\t""process_token(this, b);" "\n"
	"\t""\t""\t""\t""l = <PREFIX>_starts[this->data[this->n - 1]];" "\n"
	"\t""\t""\t""\t""ddprintf(this, \"l == %u\\n\", l);" "\n"
	"\t""\t""\t""} else {" "\n"
	"\t""\t""\t""\t""assert(!\"TODO\");" "\n"
	"\t""\t""\t""\t""exit(1);" "\n"
	"\t""\t""\t""}" "\n"
	"\t""\t""}" "\n"
	"\t""\t""l = a;" "\n"
	"\t""\t""ddprintf(this, \"l == %u\\n\", l);" "\n"
	"\t""}" "\n"
	"\t""this->lstate = l;" "\n"
	"}" "\n"
	
	"void <PREFIX>_parse_EOF(struct <PREFIX>_state* this) {" "\n"
	"\t""unsigned b, l = this->lstate;" "\n"
	"\t""ddprintf(this, \"l == %u\\n\", l);" "\n"
	"\t""if (l < N(<PREFIX>_accepts) && (b = <PREFIX>_accepts[l])) {" "\n"
	"\t""\t""process_token(this, b);" "\n"
	"\t""} else {" "\n"
	"\t""\t""assert(!\"TODO\");" "\n"
	"\t""\t""exit(1);" "\n"
	"\t""}" "\n"
	"\t""process_token(this, 1);" "\n"
	"}" "\n"
	
	"void free_<PREFIX>_state(struct <PREFIX>_state* this) {" "\n"
	"\t""free(this->data);" "\n"
	"\t""free(this);" "\n"
	"}" "\n"

"";

const char parser_header[] = ""
	"struct <PREFIX>_state;" "\n"

	"struct <PREFIX>_state* new_<PREFIX>_state();" "\n"

	"void <PREFIX>_reset(struct <PREFIX>_state* this);" "\n"

	"void <PREFIX>_parse(struct <PREFIX>_state* this, const unsigned char* text, size_t length);" "\n"

	"void <PREFIX>_parse_EOF(struct <PREFIX>_state* this);" "\n"

	"void free_<PREFIX>_state(struct <PREFIX>_state* this);" "\n"
"";


















