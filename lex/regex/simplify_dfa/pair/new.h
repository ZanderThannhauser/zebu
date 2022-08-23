
struct pair* new_pair(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* a, struct regex* b);
