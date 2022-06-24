
#include <debug.h>

#include "yacc.h"

void yacc()
{
	ENTER;
	
	// build the "firsts" set of tokens
	// for each grammar rule
	TODO;
	
	// build the "lookaheads" set of tokens
	// for each grammar rule
	TODO;
	
	// for each grammar:
		// for each lookahead token:
			// add transition to end state on lookahead token to mythical reduce state
	TODO;
	
	// for each grammar:
		// for each subgrammar-transition:
			// create lambda transition from state to start-state of subgrammar
	TODO;
	
	// nfa to dfa:
		// add more states through lambdas
		// build set of all tokens on all transitions
		// give set to tokenizer to build a scanner for
			// (might detect ambiguities)
		// call self on each set of states reached by reach transition
			// error on shift/reduce or reduce/reduce
	TODO;
	
	// dfa-simplify
	TODO;
	
	EXIT;
}












