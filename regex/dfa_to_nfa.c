
#include <debug.h>

#include "new.h"
#include "lambda_all_accepting_states.h"
#include "dfa_to_nfa.h"

struct rbundle regex_dfa_to_nfa(struct regex* dfa)
{
	ENTER;
	
	struct regex* accepts = new_regex();
	
	regex_lambda_all_accepting_states(dfa, accepts, false);
	
	EXIT;
	return (struct rbundle) {
		.is_nfa = true,
		.nfa.start = dfa,
		.nfa.accepts = accepts,
	};
}
