
struct regex* regex_simplify_dfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* original_start);
