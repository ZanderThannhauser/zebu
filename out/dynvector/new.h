
struct dynvector* new_dynvector(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* name);
