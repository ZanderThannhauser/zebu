
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/production/inside_or.h"

#include "gegex/state/add_lambda_transition.h"

#include "concat.h"
#include "or.h"

struct gbundle read_or_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle retval = read_concat_production(tokenizer, scratchpad, scope, lex);
	
	while (tokenizer->token == t_vertical_bar)
	{
		read_token(tokenizer, production_inside_or_machine);
		
		struct gbundle sub = read_concat_production(tokenizer, scratchpad, scope, lex);
		
		gegex_add_lambda_transition(retval.start, scratchpad, sub.start);
		
		gegex_add_lambda_transition(sub.end, scratchpad, retval.end);
	}
	
	EXIT;
	return retval;
}

