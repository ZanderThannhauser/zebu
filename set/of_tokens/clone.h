struct tokenset* tokenset_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const struct tokenset* othe
);
