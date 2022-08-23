
#include <debug.h>

#include "state/new.h"
#include "lambda_all_accepting_states.h"
#include "dfa_to_nfa.h"

struct rbundle regex_dfa_to_nfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* dfa)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct regex* end = new_regex(arena);
	#else
	struct regex* end = new_regex();
	#endif
	
	regex_lambda_all_accepting_states(dfa, end, false);
	
	EXIT;
	return (struct rbundle) {
		.is_nfa = true,
		.nfa.start = dfa,
		.nfa.end = end,
	};
}

