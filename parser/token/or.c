
#include <assert.h>

#include <debug.h>

#include <lex/regex/dfa_to_nfa.h>
#include <lex/regex/dotout.h>
#include <lex/regex/state/add_lambda_transition.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/regex/inside_or.h"

#include "and.h"
#include "or.h"

struct rbundle read_or_token_expression(
	struct memory_arena* arena,
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip)
{
	ENTER;
	
	struct rbundle retval = read_and_token_expression(arena, tokenizer, scope, token_skip);
	
	if (tokenizer->token == t_vertical_bar)
	{
		if (!retval.is_nfa)
		{
			retval = regex_dfa_to_nfa(retval.dfa, arena);
		}
		
		do
		{
			read_token(tokenizer, regex_inside_or_machine);
			
			struct rbundle sub = read_and_token_expression(arena, tokenizer, scope, token_skip);
			
			if (!sub.is_nfa)
			{
				sub = regex_dfa_to_nfa(sub.dfa, arena);
			}
			
			regex_add_lambda_transition(retval.nfa.start, sub.nfa.start);
			regex_add_lambda_transition(sub.nfa.end, retval.nfa.end);
			
			#ifdef DEBUGGING
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
		}
		while (tokenizer->token == t_vertical_bar);
	}
	
	EXIT;
	return retval;
}












