
#include <debug.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>

#include <parser/tokenizer/machines/regex/root.h>

#include "../root.h"

#include "parenthesis.h"

struct rbundle read_parenthesis_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope
) {
	ENTER;
	
	read_token(tokenizer, regex_root_machine);
	
	struct rbundle retval = read_root_token_expression(tokenizer, scope);
	
	if (tokenizer->token != t_cparen)
	{
		TODO;
		exit(1);
	}
	
	EXIT;
	return retval;
}
