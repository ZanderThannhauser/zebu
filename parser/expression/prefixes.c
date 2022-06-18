
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/expression_root.h"

#include "highest.h"
#include "prefixes.h"

struct bundle read_prefixes_token_expression(
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	ENTER;
	
	bool emark = false;
	
	if (tokenizer->token == t_emark)
	{
		emark = true;
		read_token(tokenizer, expression_root_machine);
	}
	
	struct bundle inner = read_highest_token_expression(scratchpad, tokenizer);
	
	if (emark)
	{
		TODO;
	}
	
	EXIT;
	return inner;
}

