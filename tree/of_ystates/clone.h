
struct ystatetree* ystatetree_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const struct ystatetree* this);
