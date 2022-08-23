struct regexset* regexset_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const struct regexset* other
);
