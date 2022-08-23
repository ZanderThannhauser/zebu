
#ifdef WITH_ARENAS

struct memory_arena;

char* arena_asprintf(
	struct memory_arena* this,
	const char* fmt, ...);


#endif
