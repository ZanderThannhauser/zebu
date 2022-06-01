
#include <debug.h>

#include "and.h"
#include "or.h"

int read_or_token_expression(
	struct regex_state** out,
	struct memory_arena* token_scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	ENTER;
	
	error = read_and_token_expression(out, token_scratchpad, tokenizer);
	
	TODO;
	
	EXIT;
	return error;
}

