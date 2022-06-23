
#include <debug.h>

#include "regex/one_or_more.h"
#include "regex/zero_or_more.h"

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/expression/after_suffix.h"

#include "prefixes.h"
#include "suffixes.h"

struct bundle read_suffixes_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope)
{
	struct bundle retval;
	
	ENTER;
	
	struct bundle inner = read_prefixes_token_expression(tokenizer, scratchpad, scope);
	
	switch (tokenizer->token)
	{
		case t_qmark:
			TODO;
			break;
		
		case t_asterisk:
		{
			struct regex* nfa = regex_zero_or_more(
				/* scratchpad: */ scratchpad,
				/* in:         */ inner.regex);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ expression_after_suffix_machine);
			
			retval = (struct bundle) {
				.is_nfa = true,
				.regex = nfa,
			};
			
			break;
		}
		
		case t_plus:
		{
			struct regex* nfa = regex_one_or_more(
				/* scratchpad: */ scratchpad,
				/* in:         */ inner.regex);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ expression_after_suffix_machine);
			
			retval = (struct bundle) {
				.is_nfa = true,
				.regex = nfa,
			};
			
			break;
		}
		
		case t_ocurly:
		{
			TODO;
			#if 0
			// repeated clones and concat
			// require accepting
			// nfa_to_dfa
			// simplify
			TODO;
			#endif
			TODO;
			break;
		}
		
		default:
			retval = inner;
			break;
	}
	
	EXIT;
	return retval;
}








