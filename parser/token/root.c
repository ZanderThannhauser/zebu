
#include <debug.h>

#include "4.or.h"

#include "root.h"

struct rbundle read_root_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	struct rbundle retval;
	ENTER;
	
	retval = read_or_token_expression(tokenizer, scope);
	
	EXIT;
	return retval;
}
