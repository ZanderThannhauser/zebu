
struct memory_arena;

int arena_sbrk(
	struct memory_arena* this,
	size_t size);
