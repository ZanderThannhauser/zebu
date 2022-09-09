
struct lex;
struct lex_state;
struct unsignedset;

struct unsignedsetset* lex_build_tokenzer(
	struct lex* this,
	struct lex_state** outgoing,
	struct unsignedset* token_ids);
