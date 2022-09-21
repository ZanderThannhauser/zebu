
#include <enums/token_kind.h>

struct lex;
struct regex;

unsigned lex_add_token(
	struct lex* this,
	struct regex* token,
	enum token_kind token_kind);
