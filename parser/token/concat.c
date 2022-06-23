
#include <debug.h>

#include "../tokenizer/struct.h"

#include "regex/concat.h"

#include "suffixes.h"
#include "concat.h"

struct bundle read_concat_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope)
{
	ENTER;
	
	struct bundle retval;
	struct bundle inner = read_suffixes_token_expression(tokenizer, scratchpad, scope);
	
	switch (tokenizer->token)
	{
		case t_oparen:
		case t_identifier:
		case t_string_literal:
		case t_dot:
		{
			struct bundle next = read_concat_token_expression(tokenizer, scratchpad, scope);
			
			regex_concat(scratchpad, inner.regex, next.regex);
			
			retval = (struct bundle) {
				.is_nfa = true,
				.regex = inner.regex,
			};
		}
		
		default:
			retval = inner;
			break;
	}
	
	EXIT;
	return retval;
}





















