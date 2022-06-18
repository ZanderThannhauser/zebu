
#include <debug.h>

#include <regex/concat.h>

#include "../tokenizer/struct.h"

#include "suffixes.h"
#include "concat.h"

struct bundle read_concat_token_expression(
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	struct bundle retval;
	struct bundle inner = read_suffixes_token_expression(scratchpad, tokenizer);
	
	if (false
		|| tokenizer->token == t_oparen
		|| tokenizer->token == t_fragment
		|| tokenizer->token == t_string_literal
		|| tokenizer->token == t_dot)
	{
		struct bundle next = read_concat_token_expression(scratchpad, tokenizer);
		
		regex_concat(scratchpad, inner.regex, next.regex);
		
		retval = (struct bundle) {
			.is_nfa = true,
			.regex = inner.regex,
		};
	}
	else
	{
		retval = inner;
	}
	
	EXIT;
	return retval;
}





















