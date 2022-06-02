
#include <debug.h>

#include "../tokenizer/struct.h"

#include "cmp.h"
#include "and.h"

int read_and_token_expression(
	bool* is_nfa_out,
	struct regex_state** out,
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	bool is_nfa;
	struct regex_state* given;
	ENTER;
	
	error = read_cmp_token_expression(&is_nfa, &given, scratchpad, tokenizer);
	
	if (!error)
	{
		if (tokenizer->token == t_and)
		{
			// create running-and (from left)
			TODO;
			
			do
			{
				// read next dfa
				// regex_and(
					// &new,
					// &running_and,
					// &next dfa);
				TODO;
				
				// free old running_and
				// running_and = new;
				TODO;
			}
			while (!error && tokenizer->token == t_and);
			
			TODO;
		}
		else
		{
			*is_nfa_out = is_nfa;
			*out = given;
		}
	}
	
	EXIT;
	return error;
}









