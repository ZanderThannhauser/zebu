
#include <stdbool.h>

struct lex;
struct regex;

unsigned lex_add_token(
	struct lex* this,
	struct regex* token,
	bool is_literal);