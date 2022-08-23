
struct iterator* new_iterator(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* state);
