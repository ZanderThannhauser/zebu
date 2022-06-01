
#include <debug.h>

#include "or.h"
#include "ternary.h"

int read_ternary_token_expression(
	struct regex_state** out,
	struct memory_arena* token_scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	ENTER;
	
	error = read_or_token_expression(out, token_scratchpad, tokenizer);
	
	TODO;
	
	EXIT;
	return error;
}

