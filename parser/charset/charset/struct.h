
#include <stdbool.h>
#include <stddef.h>

struct charset
{
	unsigned char* chars;
	size_t len;
	
	bool is_complement;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

