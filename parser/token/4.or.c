
#include <assert.h>

#include <debug.h>

#include <regex/dfa_to_nfa.h>
#include <regex/dotout.h>
#include <regex/state/add_lambda_transition.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/regex/inside_or.h"

#include "3.and.h"
#include "4.or.h"

struct rbundle read_or_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope
) {
	ENTER;
	
	struct rbundle retval = read_and_token_expression(tokenizer, scope);
	
	if (tokenizer->token == t_vertical_bar)
	{
		if (!retval.is_nfa)
		{
			retval = regex_dfa_to_nfa(retval.dfa);
		}
		
		do
		{
			read_token(tokenizer, regex_inside_or_machine);
			
			struct rbundle sub = read_and_token_expression(tokenizer, scope);
			
			if (!sub.is_nfa)
			{
				sub = regex_dfa_to_nfa(sub.dfa);
			}
			
			regex_add_lambda_transition(retval.nfa.start, sub.nfa.start);
			regex_add_lambda_transition(sub.nfa.end, retval.nfa.end);
			
			#ifdef DOTOUT
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
		}
		while (tokenizer->token == t_vertical_bar);
	}
	
	EXIT;
	return retval;
}











