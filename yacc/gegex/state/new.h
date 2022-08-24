
struct memory_arena;

struct gegex* new_gegex(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
);
