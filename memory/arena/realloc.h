
#include <stdlib.h>

struct memory_arena;

void* arena_realloc(
	struct memory_arena* this,
	void* in, size_t size);
