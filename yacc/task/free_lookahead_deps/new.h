
struct free_lookahead_deps_task* new_free_lookahead_deps_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct lookahead_deps* ldeps);
