
#include <debug.h>

#include "5.or.h"

#include "root.h"

struct rbundle read_root_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip)
{
	struct rbundle retval;
	ENTER;
	
	retval = read_or_token_expression(tokenizer, scope, token_skip);
	
	EXIT;
	return retval;
}
