
struct refcount_task* new_refcount_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* start, struct gegex* node);
