
#include <debug.h>

#include "../tokenizer/struct.h"

#include "suffixes.h"
#include "range.h"

int read_range_token_expression(
	struct regex_state** out,
	struct memory_arena* token_scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	struct regex_state* regex;
	ENTER;
	
	error = read_suffixes_token_expression(&regex, token_scratchpad, tokenizer);
	
	if (!error) switch (tokenizer->token)
	{
		case t_ellipsis:
			TODO;
			break;
		
		default:
			dpv(regex);
			*out = regex;
			break;
	}
	
	EXIT;
	return error;
}

