
struct memory_arena;
struct regex* regex_from_dot(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
);
