
#include <stddef.h>

struct memory_arena;

void mmap_free(struct memory_arena* this, void* ptr, size_t oldsize);
