
#include <debug.h>

#include "ternary.h"
#include "root.h"

int read_root_token_expression(
	struct regex_state** out,
	struct memory_arena* token_scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	ENTER;
	
	error = read_ternary_token_expression(out, token_scratchpad, tokenizer);
	
	TODO;
	
	EXIT;
	return error;
}

