
struct charset* clone_charset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const struct charset* cloneme);
