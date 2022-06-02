
#include <debug.h>

#include "../tokenizer/struct.h"

#include "highest.h"
#include "prefixes.h"

int read_prefixes_token_expression(
	bool* is_nfa_out,
	struct regex_state** out,
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_emark:
			TODO;
			break;
		
		default:
			error = read_highest_token_expression(is_nfa_out, out, scratchpad, tokenizer);
			break;
	}
	
	EXIT;
	return error;
}

