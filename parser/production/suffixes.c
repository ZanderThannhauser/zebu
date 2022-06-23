
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/production/after_suffix.h"

#include "gegex/state/add_lambda_transition.h"

#include "highest.h"
#include "suffixes.h"

struct bundle read_suffixes_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct bundle retval = read_highest_production(tokenizer, scratchpad, scope, lex);
	
	switch (tokenizer->token)
	{
		case t_plus:
			gegex_add_lambda_transition(retval.end, scratchpad, retval.start);
			read_token(tokenizer, production_after_suffix_machine);
			break;
		
		case t_asterisk:
			gegex_add_lambda_transition(retval.end, scratchpad, retval.start);
			gegex_add_lambda_transition(retval.start, scratchpad, retval.end);
			read_token(tokenizer, production_after_suffix_machine);
			break;
		
		case t_qmark:
			gegex_add_lambda_transition(retval.start, scratchpad, retval.end);
			read_token(tokenizer, production_after_suffix_machine);
			break;
		
		default:
			break;
	}
	
	EXIT;
	return retval;
}



















