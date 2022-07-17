
#include <debug.h>

#include "run_tasks.h"
#include "nfa_to_dfa.h"

#include "yacc.h"

void yacc(
	struct avl_tree_t* grammars,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	run_tasks(grammars, scratchpad);
	
	struct gegex* start = yacc_nfa_to_dfa(grammars, scratchpad);
	
	TODO;
	
	EXIT;
	// return (start, machines)
}






















