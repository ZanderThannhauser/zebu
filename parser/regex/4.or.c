
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
	
	while (tokenizer->token == t_vbar)
	{
		read_token(tokenizer);
		
		struct rbundle right = read_and_token_expression(tokenizer, scope);
		
		if (!left.accepts)
		{
			left = regex_dfa_to_nfa(left.start);
		}
		
		if (!right.accepts)
		{
			right = regex_dfa_to_nfa(right.start);
		}
		
		regex_add_lambda_transition(left.start, right.start);
		regex_add_lambda_transition(right.accepts, left.accepts);
		
		#ifdef DOTOUT
		regex_dotout(left.start, __PRETTY_FUNCTION__);
		#endif
	}
	
	EXIT;
	return left;
}











