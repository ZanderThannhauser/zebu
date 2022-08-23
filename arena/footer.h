
#ifdef WITH_ARENAS

/*#include <stdbool.h>*/

struct memory_arena_header;

struct memory_arena_footer
{
	struct memory_arena_header* header;
};

#endif
