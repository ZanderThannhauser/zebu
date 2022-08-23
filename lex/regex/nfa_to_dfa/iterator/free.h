void free_iterator(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct iterator* this
);
