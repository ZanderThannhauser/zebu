
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"

#include "and.h"
#include "or.h"

struct rbundle read_or_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope)
{
	struct rbundle retval;
	ENTER;
	
	struct rbundle inner = read_and_token_expression(tokenizer, scratchpad, scope);
	
	if (tokenizer->token == t_vertical_bar)
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
	while (!error && tokenizer->token == t_or)
	{
		// read next dfa
		// lambda given's start -> next's start
		
		TODO;
		
		is_nfa = true;
	}
	#endif




