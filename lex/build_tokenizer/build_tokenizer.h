
struct lex;
struct lex_state;
struct tokenset;

struct tokensetset* lex_build_tokenzer(
	struct lex_state** outgoing,
	struct lex* this,
	struct tokenset* token_ids);
