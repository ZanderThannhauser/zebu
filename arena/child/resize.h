
#ifdef WITH_ARENAS

#include <stdbool.h>

struct memory_arena;

bool child_resize(struct memory_arena* arena, void* ptr, size_t oldsize, size_t newsize);


#endif
