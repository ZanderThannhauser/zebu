
#include <stddef.h>

struct memory_arena;

void* arena_memdup(
	struct memory_arena* this,
	const void* data, size_t size);
