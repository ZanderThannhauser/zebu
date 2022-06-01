
#include <stdlib.h>

struct memory_arena;

int arena_malloc(
	struct memory_arena* this,
	void** ptr, size_t size);
