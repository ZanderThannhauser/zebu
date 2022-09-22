
#include <assert.h>

#include <debug.h>

#include <regex/dfa_to_nfa.h>
#include <regex/dotout.h>
#include <regex/add_lambda_transition.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "3.and.h"
#include "4.or.h"

struct rbundle read_or_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct rbundle left = read_and_token_expression(tokenizer, scope);
	
	if (tokenizer->token == t_vbar)
	{
		if (!left.is_nfa)
		{
			left = regex_dfa_to_nfa(left.dfa);
		}
		
		do
		{
			read_token(tokenizer);
			
			struct rbundle right = read_and_token_expression(tokenizer, scope);
			
			if (!right.is_nfa)
			{
				right = regex_dfa_to_nfa(right.dfa);
			}
			
			regex_add_lambda_transition(left.nfa.start, right.nfa.start);
			regex_add_lambda_transition(right.nfa.accepts, left.nfa.accepts);
			
			#ifdef DOTOUT
			regex_dotout(left.nfa.start, __PRETTY_FUNCTION__);
			#endif
		}
		while (tokenizer->token == t_vbar);
	}
	
	EXIT;
	return left;
}











