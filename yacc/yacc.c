
#include <debug.h>

#include "run_tasks.h"
#include "nfa_to_dfa.h"

#include "yacc.h"

void yacc(
	struct lex* lex,
	struct avl_tree_t* grammars,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	run_tasks(grammars, scratchpad);
	
	// at this point, we have one nfa parser state machine, with reduction
	// transitions
	
	struct gegex* start = yacc_nfa_to_dfa(lex, grammars, scratchpad);
	
	// simplify?
	TODO;
	
	EXIT;
	// return start
}






















