
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/token_names.h>
#include <parser/tokenizer/read_token.h>

#include "../root.h"

#include "parenthesis.h"

struct gbundle read_parenthesis_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
	ENTER;
	
	read_token(tokenizer);
	
	retval = read_root_production(tokenizer, scope, lex);
	
	if (tokenizer->token != t_cparen)
	{
		fprintf(stderr, "zebu: encountered syntax error on line %u: "
			"unexpected '%s', expecting '%s'!\n", tokenizer->line,
			token_names[tokenizer->token],
			token_names[t_cparen]);
		exit(e_syntax_error);
	}
	
	read_token(tokenizer);
	
	EXIT;
	return retval;
}













