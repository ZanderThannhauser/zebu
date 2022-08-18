
#include <stdlib.h>

#include <debug.h>

#include <set/of_gegexes/free.h>

#include "struct.h"
#include "free.h"

void free_lookahead_deps_node(void* ptr)
{
	struct lookahead_deps_node* node = ptr;
	
	free_gegexset(node->b);
	
	free(node);
}

