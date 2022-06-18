
#include <debug.h>

#include <regex/from_literal.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/expression_after_highest.h"

#include "highest.h"

struct bundle read_highest_token_expression(
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer)
{
	struct bundle retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_string_literal:
		{
			dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
			
			dpvsn(tokenizer->tokenchars.chars + 1, tokenizer->tokenchars.n - 2);
			
			struct regex* start = regex_from_literal(
				/* scratchpad: */ scratchpad,
				/* chars:      */ tokenizer->tokenchars.chars + 1,
				/* strlen:     */ tokenizer->tokenchars.n - 2);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ expression_after_highest_machine);
			
			retval = (struct bundle) {
				.regex = start,
				.is_nfa = false,
			};
			
			break;
		}
		
		case t_osquare:
		{
			TODO;
			break;
		}
		
		case t_oparen:
		{
			TODO;
			break;
		}
		
		case t_identifier:
		{
			TODO;
			break;
		}
		
		case t_dot:
		{
			TODO;
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return retval;
}

