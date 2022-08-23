struct gegex_pair* new_gegex_pair(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* a, struct gegex* b
);
