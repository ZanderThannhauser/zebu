
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/expression/inside_and.h"

#include "regex/state/struct.h"
#include "regex/state/free.h"
#include "regex/intersect_dfas/intersect_dfas.h"
#include "regex/nfa_to_dfa/nfa_to_dfa.h"
#include "regex/simplify_dfa/simplify_dfa.h"

#include "concat.h"
#include "and.h"

struct rbundle read_and_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope)
{
	struct rbundle retval;
	ENTER;
	
	struct rbundle left = read_concat_token_expression(tokenizer, scratchpad, scope);
	
	if (tokenizer->token == t_ampersand)
	{
		read_token(tokenizer, expression_inside_and_machine);
		
		struct rbundle right = read_and_token_expression(tokenizer, scratchpad, scope);
		
		struct regex* left_machine;
		
		if (left.is_nfa)
		{
			TODO;
		}
		else
		{
			left_machine = left.dfa;
		}
		
		struct regex* right_machine;
		
		if (right.is_nfa)
		{
			right.nfa.end->is_accepting = true;
			
			struct regex* nfa = right.nfa.start;
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
		
		retval = (struct rbundle) {
			.is_nfa = false,
			.dfa = outgoing,
		};
	}
	else
	{
		retval = left;
	}
	
	EXIT;
	return retval;
}

















