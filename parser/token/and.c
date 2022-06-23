
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/expression/inside_and.h"

#include "regex/state/free.h"
#include "regex/intersect_dfas/intersect_dfas.h"
#include "regex/nfa_to_dfa/nfa_to_dfa.h"
#include "regex/simplify_dfa/simplify_dfa.h"

#include "concat.h"
#include "and.h"

struct bundle read_and_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope)
{
	struct bundle retval;
	ENTER;
	
	struct bundle left = read_concat_token_expression(tokenizer, scratchpad, scope);
	
	if (tokenizer->token == t_ampersand)
	{
		read_token(tokenizer, expression_inside_and_machine);
		
		struct bundle right = read_and_token_expression(tokenizer, scratchpad, scope);
		
		struct regex* left_machine;
		
		if (left.is_nfa)
		{
			TODO;
		}
		else
		{
			left_machine = left.regex;
		}
		
		struct regex* right_machine;
		
		if (right.is_nfa)
		{
			struct regex* nfa = right.regex;
			struct regex* dfa = regex_nfa_to_dfa(nfa, scratchpad);
			
			right_machine = regex_simplify_dfa(dfa, scratchpad);
			
			free_regex(nfa, scratchpad), free_regex(dfa, scratchpad);
		}
		else
		{
			TODO;
		}
		
		dpv(left_machine);
		dpv(right_machine);
		
		struct regex* intersected = regex_intersect_dfas(left_machine, right_machine, scratchpad);
		
		struct regex* outgoing = regex_simplify_dfa(intersected, scratchpad);
		
		free_regex(intersected, scratchpad);
		
		retval = (struct bundle) {
			.regex = outgoing,
			.is_nfa = false,
		};
	}
	else
	{
		retval = left;
	}
	
	EXIT;
	return retval;
}

















