
#include <stddef.h>
#include <stdbool.h>

struct memory_arena_header
{
	bool is_alloc;
	size_t size;
	struct memory_arena_header *prev, *next;
};

