
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/production/after_suffix.h"

#include <yacc/gegex/state/add_lambda_transition.h>
#include <yacc/gegex/dotout.h>

#include "highest.h"
#include "suffixes.h"

struct gbundle read_suffixes_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle retval = read_highest_production(tokenizer, scratchpad, options, scope, lex);
	
	dpv(retval.start);
	dpv(retval.end);
	
	switch (tokenizer->token)
	{
		case t_plus:
			dputs("t_plus");
			gegex_add_lambda_transition(retval.end, scratchpad, retval.start);
			read_token(tokenizer, production_after_suffix_machine);
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end);
			#endif
			break;
		
		case t_asterisk:
			dputs("t_asterisk");
			gegex_add_lambda_transition(retval.end, scratchpad, retval.start);
			gegex_add_lambda_transition(retval.start, scratchpad, retval.end);
			read_token(tokenizer, production_after_suffix_machine);
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end);
			#endif
			break;
		
		case t_qmark:
			dputs("t_qmark");
			gegex_add_lambda_transition(retval.start, scratchpad, retval.end);
			read_token(tokenizer, production_after_suffix_machine);
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end);
			#endif
			break;
		
		default:
			break;
	}
	
	EXIT;
	return retval;
}



















