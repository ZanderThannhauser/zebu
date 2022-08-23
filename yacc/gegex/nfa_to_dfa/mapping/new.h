
struct gegex_mapping* new_gegex_mapping(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegextree* set, struct gegex* state);
