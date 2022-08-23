
struct charset* charset_union(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const struct charset* a,
	const struct charset* b,
	bool is_complement);
