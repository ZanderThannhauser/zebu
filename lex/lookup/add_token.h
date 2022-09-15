
#include <enums/token_kind.h>

struct lex;
struct regex;

unsigned lex_add_token2(
	struct lex* this,
	struct regex* token,
	enum token_kind token_kind);
