
#include <debug.h>

#include <regex/one_or_more.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/expression_after_suffix.h"

#include "prefixes.h"
#include "suffixes.h"

int read_suffixes_token_expression(
	bool* is_nfa_out,
	struct regex_state** out,
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	bool is_nfa;
	struct regex_state* given;
	struct regex_state* nfa;
	ENTER;
	
	error = read_prefixes_token_expression(&is_nfa, &given, scratchpad, tokenizer);
	
	if (!error) switch (tokenizer->token)
	{
		case t_qmark:
			TODO;
			break;
		
		case t_asterisk:
			TODO;
			break;
		
		case t_plus:
		{
			error = 0
				?: regex_one_or_more(
					/* out:        */ &nfa,
					/* scratchpad: */ scratchpad,
					/* in:         */ given)
				?: read_token(
					/* tokenizer: */ tokenizer,
					/* machine:   */ expression_after_suffix_machine);
			
			if (!error)
			{
				*is_nfa_out = true;
				*out = nfa;
			}
			
			break;
		}
		
		case t_ocurly:
		{
			// repeated clones and concat
			// require accepting
			// nfa_to_dfa
			// simplify
			TODO;
			break;
		}
		
		default:
		{
			*is_nfa_out = is_nfa;
			*out = given;
			break;
		}
	}
	
	EXIT;
	return error;
}








