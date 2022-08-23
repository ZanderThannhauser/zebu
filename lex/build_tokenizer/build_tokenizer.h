
struct lex_state;

struct tokenset;
struct lex;

struct tokensetset* lex_build_tokenzer(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct lex_state** outgoing,
	struct lex* this,
	struct tokenset* token_ids);
