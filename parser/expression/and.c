
#include <debug.h>

#include "../tokenizer/struct.h"

#include "concat.h"
#include "and.h"

struct bundle read_and_token_expression(
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	struct bundle retval;
	struct bundle inner = read_concat_token_expression(scratchpad, tokenizer);
	
	if (tokenizer->token == t_and)
	{
		TODO;
	}
	else
	{
		retval = inner;
	}
	
	EXIT;
	return retval;
}









	#if 0
	int error = 0;
	bool is_nfa;
	struct regex_state* given;
	ENTER;
	
	error = 
	
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
	#endif
