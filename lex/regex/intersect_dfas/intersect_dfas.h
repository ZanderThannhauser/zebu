
struct regex* regex_intersect_dfas(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* A,
	struct regex* B);
