
struct task;

void free_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct task* this);
