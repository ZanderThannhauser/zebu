
struct explore_firsts_task* new_explore_firsts_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* start,
	const char* name,
	struct gegex* node);
