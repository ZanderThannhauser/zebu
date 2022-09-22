
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <parser/tokenizer/struct.h>
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
		TODO;
		exit(1);
	}
	
	EXIT;
	return retval;
}
