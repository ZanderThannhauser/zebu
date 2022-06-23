
#include <debug.h>

#include "../tokenizer/struct.h"

#include "gegex/state/add_lambda_transition.h"

#include "subdefinitions.h"
#include "concat.h"

struct bundle read_concat_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct bundle retval;
	
	struct bundle left = read_subdefinitions_production(tokenizer, scratchpad, scope, lex);
	
	switch (tokenizer->token)
	{
		case t_string_literal:
		case t_character_literal:
		case t_oparen:
		case t_identifier:
		case t_gravemark:
		{
			struct bundle right = read_concat_production(tokenizer, scratchpad, scope, lex);
			
			gegex_add_lambda_transition(left.end, scratchpad, right.start);
			
			retval = (struct bundle) {left.start, right.end};
			break;
		}
		
		default:
			retval = left;
			break;
	}
	
	EXIT;
	return retval;
}

