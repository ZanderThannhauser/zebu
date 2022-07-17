
#include <debug.h>

#include "state/new.h"
#include "lambda_all_accepting_states.h"
#include "dfa_to_nfa.h"

struct rbundle regex_dfa_to_nfa(
	struct regex* dfa,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	struct regex* end = new_regex(scratchpad);
	
	regex_lambda_all_accepting_states(dfa, scratchpad, end, false);
	
	EXIT;
	return (struct rbundle) {
		.is_nfa = true,
		.nfa.start = dfa,
		.nfa.end = end,
	};
}

