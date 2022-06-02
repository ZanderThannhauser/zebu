
#include <debug.h>

#include "ternary.h"
#include "root.h"

int read_root_token_expression(
	bool* is_nfa_out,
	struct regex_state** out,
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	ENTER;
	
	error = read_ternary_token_expression(is_nfa_out, out, scratchpad, tokenizer);
	
	TODO;
	
	EXIT;
	return error;
}

