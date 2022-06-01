
#include <stdlib.h>

struct memory_arena;

int arena_realloc(
	struct memory_arena* this,
	void** ptr, size_t size);
