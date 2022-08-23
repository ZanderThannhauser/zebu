
struct yacc_state;
struct lex;
struct memory_arena;

void lex_simplify_tokenizer(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct lex* this,
	struct yacc_state* start);
