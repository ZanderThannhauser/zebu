
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <enums/error.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/token_names.h>
#include <parser/tokenizer/read_token.h>

#include "../root.h"

#include "parenthesis.h"

struct rbundle read_parenthesis_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	assert(tokenizer->token == t_oparen);
	
	read_token(tokenizer);
	
	struct rbundle retval = read_root_token_expression(tokenizer, scope);
	
	if (tokenizer->token != t_cparen)
	{
		fprintf(stderr, "zebu: encountered syntax error on line %u: "
			"unexpected '%s', expecting '%s'!\n",
			tokenizer->line,
			token_names[tokenizer->token],
			token_names[t_cparen]);
		exit(e_syntax_error);
	}
	
	EXIT;
	return retval;
}
