
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/regex/inside_and.h"

#include <lex/regex/state/struct.h>
#include <lex/regex/state/free.h>
#include <lex/regex/intersect_dfas/intersect_dfas.h>
#include <lex/regex/nfa_to_dfa/nfa_to_dfa.h>
#include <lex/regex/simplify_dfa/simplify_dfa.h>

#include "concat.h"
#include "and.h"

struct rbundle read_and_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope)
{
	ENTER;
	
	struct rbundle retval = read_concat_token_expression(tokenizer, scratchpad, scope);
	
	while (tokenizer->token == t_ampersand)
	{
		read_token(tokenizer, regex_inside_and_machine);
		
		struct rbundle right = read_concat_token_expression(tokenizer, scratchpad, scope);
		
		struct regex* left_machine;
		
		if (retval.is_nfa)
		{
			TODO;
		}
		else
		{
			left_machine = retval.dfa;
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
			right_machine = right.dfa;
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
	
	EXIT;
	return retval;
}

















