
#include <debug.h>

#include <regex/one_or_more.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/expression_after_suffix.h"

#include "prefixes.h"
#include "suffixes.h"

struct bundle read_suffixes_token_expression(
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	struct bundle retval;
	
	ENTER;
	struct bundle inner = read_prefixes_token_expression(scratchpad, tokenizer);
	
	switch (tokenizer->token)
	{
		case t_qmark:
			TODO;
			break;
		
		case t_asterisk:
			TODO;
			break;
		
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
		{
			TODO;
			#if 0
			*is_nfa_out = is_nfa;
			*out = given;
			#endif
			break;
		}
	}
	
	EXIT;
	return retval;
}








