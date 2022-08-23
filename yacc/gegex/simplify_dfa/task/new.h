
struct gegex_simplify_task* new_gegex_simplify_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* a, struct gegex* b,
	unsigned hopcount);
