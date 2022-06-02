
#include <debug.h>

#include <regex/concat.h>

#include "../tokenizer/struct.h"

#include "range.h"
#include "concat.h"

int read_concat_token_expression(
	bool* is_nfa_out,
	struct regex_state** out,
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	bool _;
	struct regex_state* left;
	ENTER;
	
	error = read_range_token_expression(&_, &left, scratchpad, tokenizer);
	
	if (!error) switch (tokenizer->token)
	{
		
		struct regex_state* right;
		
		case t_oparen:
		case t_fragment:
		case t_string_literal:
		case t_dot:
		{
			error = 0
				?: read_concat_token_expression(&_, &right, scratchpad, tokenizer)
				?: regex_concat(scratchpad, left, right);
			
			*is_nfa_out = true;
			*out = left;
			break;
		}
		
		default:
		{
			dpv(left);
			*out = left;
			break;
		}
	}
	
	EXIT;
	return error;
}





















