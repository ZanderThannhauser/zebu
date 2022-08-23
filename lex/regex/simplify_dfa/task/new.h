
struct simplify_task* new_simplify_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* a, struct regex* b,
	unsigned hopcount);
