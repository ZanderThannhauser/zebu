
#include <debug.h>

#include "../tokenizer/struct.h"

#include "or.h"
#include "ternary.h"

int read_ternary_token_expression(
	bool* is_nfa_out,
	struct regex_state** out,
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	bool is_nfa;
	struct regex_state* given;
	ENTER;
	
	error = read_or_token_expression(&is_nfa, &given, scratchpad, tokenizer);
	
	if (!error)
	{
		if (tokenizer->token == t_qmark)
		{
			// next token
			
			// read_ternary_token_expression()
			
			// assert colon
			
			// read_ternary_token_expression()
			
			TODO;
		}
		else
		{
			TODO;
		}
	}
	
	TODO;
	
	EXIT;
	return error;
}

