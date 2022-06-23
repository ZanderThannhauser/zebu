
struct lex;
struct regex;

unsigned lex_get_token_id(
	struct lex* this,
	struct regex* token);
