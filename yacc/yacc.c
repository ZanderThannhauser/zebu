
#include <debug.h>

#include <lex/struct.h>

#include <yacc/state/dotout.h>

#include "shared/struct.h"
#include "shared/new.h"

#include "run_tasks.h"
#include "nfa_to_dfa.h"
#include "yacc.h"

struct yacc_state* yacc(
	struct yacc_shared** out_shared,
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	struct yacc_shared* shared = new_yacc_shared(grammar, lex->EOF_token_id);
	
	run_tasks(shared, scratchpad);
	
	struct yacc_state* start = yacc_nfa_to_dfa(lex, shared->new_grammar, scratchpad);
	
	#ifdef DEBUGGING
	yacc_state_dotout(start);
	#endif
	
	*out_shared = shared;
	
	EXIT;
	return start;
}






















