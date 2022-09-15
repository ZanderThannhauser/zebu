
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/production/root.h>
#include <parser/tokenizer/machines/production/after_highest.h>

#include "../root.h"

#include "parenthesis.h"

struct gbundle read_parenthesis_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
	ENTER;
	
	read_token(tokenizer, production_root_machine);
	
	retval = read_root_production(tokenizer, scope, lex);
	
	if (tokenizer->token != t_cparen)
	{
		TODO;
		exit(1);
	}
	
	read_token(tokenizer, production_after_highest_machine);
	
	EXIT;
	return retval;
}


