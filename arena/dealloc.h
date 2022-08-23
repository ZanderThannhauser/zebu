
#ifdef WITH_ARENAS

struct memory_arena;

void arena_dealloc(
	struct memory_arena* this,
	void* ptr);


#endif
