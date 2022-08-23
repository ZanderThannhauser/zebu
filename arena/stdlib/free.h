
#ifdef WITH_ARENAS

#include <stdlib.h>

struct memory_arena;

void stdlib_free(struct memory_arena* this, void* ptr, size_t oldsize);


#endif
