
#include <stdlib.h>

struct memory_arena;

void* arena_malloc(struct memory_arena* this, size_t user_size);
