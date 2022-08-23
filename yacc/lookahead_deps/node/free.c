
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include <set/of_gegexes/free.h>

#include "struct.h"
#include "free.h"

void free_lookahead_deps_node(void* ptr)
{
	struct lookahead_deps_node* const node = ptr;
	ENTER;
	
	free_gegexset(node->b);
	
	#ifdef WITH_ARENAS
	arena_dealloc(node->arena, node);
	#else
	free(node);
	#endif
	
	EXIT;
}

