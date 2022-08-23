
struct named_strset* new_named_strset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* name, struct strset* strset);
