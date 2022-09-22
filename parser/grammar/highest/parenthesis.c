
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <parser/tokenizer/struct.h>
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
		TODO;
		exit(1);
	}
	
	read_token(tokenizer);
	
	EXIT;
	return retval;
}


