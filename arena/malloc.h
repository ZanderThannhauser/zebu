
#ifdef WITH_ARENAS

#include <stddef.h>

struct memory_arena;

void* arena_malloc(struct memory_arena* this, size_t size);


#endif
