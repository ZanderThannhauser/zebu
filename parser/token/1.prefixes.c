
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/regex/inside_emark.h"

#include <regex/complement.h>

#include "0.highest.h"
#include "1.prefixes.h"

struct rbundle read_prefixes_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope
) {
	struct rbundle retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_emark:
		{
			read_token(tokenizer, regex_inside_emark_machine);
			
			struct rbundle inner = read_highest_token_expression(tokenizer, scope);
			
			struct regex* machine;
			
			if (inner.is_nfa)
			{
	/*			right.nfa.end->is_accepting = true;*/
	/*			*/
	/*			struct regex* nfa = right.nfa.start;*/
	/*			struct regex* dfa = regex_nfa_to_dfa(nfa, scratchpad);*/
	/*			*/
	/*			right_machine = regex_simplify_dfa(dfa, scratchpad);*/
	/*			*/
	/*			free_regex(nfa, scratchpad), free_regex(dfa, scratchpad);*/
				TODO;
			}
			else
			{
				machine = inner.dfa;
			}
			
			regex_complement(machine);
			
			EXIT;
			return (struct rbundle) {
				.is_nfa = false,
				.dfa = machine,
			};
		}
		
		default:
		{
			retval = read_highest_token_expression(tokenizer, scope);
			break;
		}
	}
	
	EXIT;
	return retval;
}









