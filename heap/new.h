
struct memory_arena;

struct heap* new_heap(
	struct memory_arena* arena,
	int (*cmp)(const void*, const void*));
