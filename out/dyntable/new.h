
struct dyntable* new_dyntable(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* name);
