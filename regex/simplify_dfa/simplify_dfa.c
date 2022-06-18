
#include <debug.h>

#include "simplify_dfa.h"

struct regex* regex_simplify_dfa(
	struct regex* original,
	struct memory_arena* arena)
{
	ENTER;
	
	// recursive
	
	// avl_tree mapping two nodes to whether they are different for some input:
		// default to not different
		// if one is accepting and another is not:
			// definately different
		// for each of their inputs:
			// call self on the transitioned-to node-pairs
				// (possibly using defaults)
			// if subpair is different:
				// than this pair is different too
	
	TODO;
	
	EXIT;
}

