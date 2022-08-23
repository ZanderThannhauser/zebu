struct gegexset* gegexset_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const struct gegexset* other
);
