
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

#include <debug.h>

#include <regex/dfa_to_nfa.h>
#include <regex/add_lambda_transition.h>
#include <regex/struct.h>
#include <regex/free.h>
#include <regex/nfa_to_dfa.h>
#include <regex/simplify_dfa.h>

#include <parser/regex/root.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>

#include <lex/struct.h>
#include <lex/add_token.h>

#include "skip.h"

void read_skip_directive(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_identifier);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_colon)
	{
		TODO;
		exit(1);
	}
	
	read_token(tokenizer);
	
	struct rbundle regex = read_root_token_expression(tokenizer, scope);
	
	if (!regex.is_nfa)
	{
		regex = regex_dfa_to_nfa(regex.dfa);
	}
	
	regex_add_lambda_transition(regex.nfa.accepts, regex.nfa.start);
	
	struct regex* dfa = regex_nfa_to_dfa(regex);
	
	struct regex* simp = regex_simplify_dfa(dfa);
	
	unsigned token_id = lex_add_token(lex, simp, tk_whitespace);
	
	dpv(token_id);
	
	lex->whitespace_token_id = token_id;
	
	free_regex(regex.nfa.start), free_regex(dfa);
	
	EXIT;
}













