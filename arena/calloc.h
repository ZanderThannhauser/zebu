
#include <sys/types.h>

struct memory_arena;

void* arena_calloc(
	struct memory_arena* this,
	size_t nmemb, size_t size);
