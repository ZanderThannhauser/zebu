struct lex_state* new_lex_state(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
);
