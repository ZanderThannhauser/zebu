
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
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle retval = read_highest_production(grammar_arena, token_arena, tokenizer, options, scope, lex);
	
	dpv(retval.start);
	dpv(retval.end);
	
	switch (tokenizer->token)
	{
		case t_plus:
		{
			gegex_add_lambda_transition(retval.end, retval.start);
			
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer, production_after_suffix_machine);
			
			break;
		}
		
		case t_asterisk:
		{
			gegex_add_lambda_transition(retval.end,retval.start);
			gegex_add_lambda_transition(retval.start, retval.end);
			
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer, production_after_suffix_machine);
			break;
		}
		
		case t_qmark:
		{
			gegex_add_lambda_transition(retval.start, retval.end);
			
			#ifdef DEBUGGING
			gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer, production_after_suffix_machine);
			break;
		}
		
		default:
			break;
	}
	
	EXIT;
	return retval;
}



















