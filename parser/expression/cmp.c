
#include <debug.h>

#include "simp.h"
#include "cmp.h"

int read_cmp_token_expression(
	struct regex_state** out,
	struct memory_arena* token_scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	ENTER;
	
	error = read_simp_token_expression(out, token_scratchpad, tokenizer);
	
	TODO;
	
	EXIT;
	return error;
}

