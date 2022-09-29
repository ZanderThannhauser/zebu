
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

#include <debug.h>

#include <enums/error.h>

#include <regex/dfa_to_nfa.h>
#include <regex/add_lambda_transition.h>
#include <regex/struct.h>
#include <regex/free.h>
#include <regex/nfa_to_dfa.h>
#include <regex/simplify_dfa.h>

#include <parser/regex/root.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/token_names.h>

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
		fprintf(stderr, "zebu: encountered syntax error on line %u: "
			"unexpected '%s', expecting '%s'!\n",
			tokenizer->line,
			token_names[tokenizer->token],
			token_names[t_colon]);
		exit(e_syntax_error);
	}
	
	read_token(tokenizer);
	
	struct rbundle regex = read_root_token_expression(tokenizer, scope);
	
	if (!regex.accepts)
		regex = regex_dfa_to_nfa(regex.start);
	
	regex_add_lambda_transition(regex.accepts, regex.start);
	
	struct regex* dfa = regex_nfa_to_dfa(regex);
	
	struct regex* simp = regex_simplify_dfa(dfa);
	
	unsigned token_id = lex_add_token(lex, simp, tk_whitespace);
	
	dpv(token_id);
	
	lex->whitespace_token_id = token_id;
	
	if (tokenizer->token != t_semicolon)
	{
		fprintf(stderr, "zebu: encountered syntax error on line %u: "
			"unexpected '%s', expecting '%s'!\n",
			tokenizer->line,
			token_names[tokenizer->token],
			token_names[t_semicolon]);
		exit(e_syntax_error);
	}
	
	read_token(tokenizer);
	
	free_regex(regex.start), free_regex(dfa);
	
	EXIT;
}













