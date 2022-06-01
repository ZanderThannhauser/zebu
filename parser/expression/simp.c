
#include <debug.h>

#include <regex/dotout.h>

#include "concat.h"
#include "simp.h"

int read_simp_token_expression(
	struct regex_state** out,
	struct memory_arena* token_scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	struct regex_state* nfa;
	ENTER;
	
	error = read_concat_token_expression(&nfa, token_scratchpad, tokenizer);
	
	#ifdef DEBUGGING
	
	regex_dotout(nfa);
	
	CHECK;
	
	#endif
	
	struct regex_state* dfa;
	
	// error = regex_nfa_to_dfa()
	TODO;
	
	// error = regex_simplify_dfa()
	TODO;
	
	#ifdef DEBUGGING
	
	regex_dotout(dfa);
	
	CHECK;
	
	#endif
	
	TODO;
	
	EXIT;
	return error;
}









