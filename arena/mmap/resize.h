
#include <stdbool.h>
#include <stddef.h>

struct memory_arena;

bool mmap_resize(struct memory_arena* this, void* ptr, size_t oldsize, size_t newsize);
