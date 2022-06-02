
#include <debug.h>

#include "../tokenizer/struct.h"

#include "suffixes.h"
#include "range.h"

int read_range_token_expression(
	bool* is_nfa_out,
	struct regex_state** out,
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	bool is_nfa;
	struct regex_state* given;
	ENTER;
	
	error = read_suffixes_token_expression(&is_nfa, &given, scratchpad, tokenizer);
	
	if (!error) switch (tokenizer->token)
	{
		case t_ellipsis:
		{
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

