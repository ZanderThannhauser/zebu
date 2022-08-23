
#ifdef WITH_ARENAS

#include <stddef.h>

struct memory_arena;

void* stdlib_realloc(struct memory_arena* this, void* ptr, size_t newsize);


#endif
