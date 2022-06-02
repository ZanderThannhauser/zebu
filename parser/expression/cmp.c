
#include <debug.h>

#include "../tokenizer/struct.h"

#include "concat.h"
#include "cmp.h"

int read_cmp_token_expression(
	bool* is_nfa_out,
	struct regex_state** out,
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	bool is_nfa;
	struct regex_state* given;
	ENTER;
	
	error = read_concat_token_expression(&is_nfa, &given, scratchpad, tokenizer);
	
	if (!error) switch (tokenizer->token)
	{
		case t_gthan:
		case t_gthan_eq:
		case t_lthan:
		case t_lthan_eq:
		case t_equal_to:
		case t_not_equal_to:
		{
			// read second dfa
			
			// do operation
			
			// add to running-and
			
			// keep reference to second one for next iteration
			
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

