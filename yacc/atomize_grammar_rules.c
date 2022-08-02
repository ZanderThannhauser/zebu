
#include <debug.h>

#include "atomize_grammar_rules.h"

struct avl_tree_t* atomize_grammar_rules(
	struct avl_tree_t* original_rules,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	// break each grammar rule into many small rules
	// with each production rule knowing how much pop
	
	// if transition->to->reduction_point:
		// ".%s.%u" ( ) -> token/grammar -> ( )                      // (pop once)
	// else:
		// ".%s.%u" ( ) -> token/grammar -> ( ) -> ".%s.%u+1" -> ( ) // (pop twice)
	
	TODO;
	
	EXIT;
}

