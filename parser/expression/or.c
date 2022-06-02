
#include <debug.h>

#include "../tokenizer/struct.h"

#include "and.h"
#include "or.h"

int read_or_token_expression(
	bool* is_nfa_out,
	struct regex_state** out,
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	bool is_nfa;
	struct regex_state* given;
	ENTER;
	
	error = read_and_token_expression(&is_nfa, &given, scratchpad, tokenizer);
	
	while (!error && tokenizer->token == t_or)
	{
		// read next dfa
		// lambda given's start -> next's start
		
		TODO;
		
		is_nfa = true;
	}
	
	if (!error)
	{
		*is_nfa_out = is_nfa;
		*out = given;
	}
	
	EXIT;
	return error;
}











