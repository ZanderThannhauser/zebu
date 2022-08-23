
#include <assert.h>

#include <debug.h>

#include "simplify_tokenizer.h"

void lex_simplify_tokenizer(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct lex* this,
	struct yacc_state* start)
{
	ENTER;
	
	// iterate through all machines, adding the lex_states into
	// the universe set
	TODO;
	
	// run n^2 setup loop
	TODO;
	
	// run percolate tasks
	TODO;
	
	// clone machine
	TODO;
	
	// iterate through every yacc state, looking up old to new lex state
	TODO;
	
	EXIT;
}

