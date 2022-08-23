struct regex* new_regex(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
);
