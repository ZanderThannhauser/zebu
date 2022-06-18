
struct memory_arena;

void* arena_sbrk(
	struct memory_arena* this,
	size_t requested_size);
