
#include <debug.h>

#include <regex/concat.h>

#include "../tokenizer/struct.h"

#include "range.h"
#include "concat.h"

int read_concat_token_expression(
	struct regex_state** out,
	struct memory_arena* token_scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	struct regex_state* left;
	ENTER;
	
	error = read_range_token_expression(&left, token_scratchpad, tokenizer);
	
	if (!error) switch (tokenizer->token)
	{
		
		struct regex_state* right;
		
		case t_oparen:
		case t_fragment:
		case t_string_literal:
		case t_dot:
		{
			error = 0
				?: read_concat_token_expression(&right, token_scratchpad, tokenizer)
				?: regex_concat(token_scratchpad, left, right);
			
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











