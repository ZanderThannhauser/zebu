
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/expression/root.h"

#include "regex/complement.h"

#include "highest.h"
#include "prefixes.h"

struct bundle read_prefixes_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope)
{
	ENTER;
	
	bool emark = false;
	
	if (tokenizer->token == t_emark)
	{
		emark = true;
		read_token(tokenizer, expression_root_machine);
	}
	
	struct bundle retval;
	struct bundle inner = read_highest_token_expression(tokenizer, scratchpad, scope);
	
	if (emark)
	{
		struct regex* machine;
		
		if (inner.is_nfa)
		{
			TODO;
		}
		else
		{
			machine = inner.regex;
		}
		
		regex_complement(machine);
		
		retval = (struct bundle) {
			.regex = machine,
			.is_nfa = false,
		};
	}
	else
	{
		retval = inner;
	}
	
	EXIT;
	return inner;
}










