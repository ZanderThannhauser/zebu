
struct memory_arena;

struct heap* new_heap(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	int (*cmp)(const void*, const void*));
