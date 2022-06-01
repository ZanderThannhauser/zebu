
#include <debug.h>

#include <regex/one_or_more.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/expression_after_suffix.h"

#include "prefixes.h"
#include "suffixes.h"

int read_suffixes_token_expression(
	struct regex_state** out,
	struct memory_arena* token_scratchpad,
	struct tokenizer* tokenizer)
{
	int error = 0;
	struct regex_state* regex;
	ENTER;
	
	error = read_prefixes_token_expression(&regex, token_scratchpad, tokenizer);
	
	if (!error) switch (tokenizer->token)
	{
		case t_qmark:
			TODO;
			break;
		
		case t_asterisk:
			TODO;
			break;
		
		case t_plus:
		{
			error = 0
				?: regex_one_or_more(
					/* out:        */ &regex,
					/* scratchpad: */  token_scratchpad,
					/* in:         */  regex)
				?: read_token(
					/* tokenizer: */ tokenizer,
					/* machine:   */ expression_after_suffix_machine);
			
			if (!error)
				*out = regex;
			
			break;
		}
		
		case t_ocurly:
			TODO;
			break;
		
		default:
			*out = regex;
			break;
	}
	
	EXIT;
	return error;
}








