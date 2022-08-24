
struct lstatetree* lstatetree_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const struct lstatetree* this);
