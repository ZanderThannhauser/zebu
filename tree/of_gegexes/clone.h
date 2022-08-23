struct gegextree* gegextree_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegextree* this
);
