
#ifdef WITH_ARENAS

#include <stddef.h>

struct memory_arena;

void* mmap_malloc(struct memory_arena* this, size_t size);


#endif
