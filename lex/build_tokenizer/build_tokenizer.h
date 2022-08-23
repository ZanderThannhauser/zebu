
struct memory_arena;
struct tokenset;
struct lex;
struct lex_state;

struct tokensetset* lex_build_tokenzer(
	struct memory_arena* arena,
	struct lex_state** outgoing,
	struct lex* this,
	struct tokenset* token_ids);
