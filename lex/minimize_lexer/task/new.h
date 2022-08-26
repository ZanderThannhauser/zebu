
struct lex_simplify_task* new_lex_simplify_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct lex_state* a, struct lex_state* b,
	unsigned hopcount);
