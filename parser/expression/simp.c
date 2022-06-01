
#include <debug.h>

#include <regex/nfa_to_dfa.h>
#include <regex/simplify.h>

#include "concat.h"
#include "simp.h"

int read_simp_token_expression(
	struct regex_state** out,
	struct memory_arena* token_scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	struct regex_state* nfa;
	struct regex_state* dfa;
	struct regex_state* simp;
	ENTER;
	
	error = 0
		?: read_concat_token_expression(&nfa, token_scratchpad, tokenizer)
		?: regex_nfa_to_dfa(&dfa, token_scratchpad, nfa)
		?: regex_simplify(&simp, dfa);
	
	if (!error)
		*out = simp;
	
	EXIT;
	return error;
}









