
#include <assert.h>

#include <debug.h>

#include <gegex/add_lambda_transition.h>
#include <gegex/dotout.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "0.highest.h"
#include "1.suffixes.h"

struct gbundle read_suffixes_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle retval = read_highest_production(tokenizer, scope, lex);
	
	switch (tokenizer->token)
	{
		case t_plus:
		{
			TODO;
			#if 0
			gegex_add_lambda_transition(retval.end, retval.start);
			
			#ifdef DOTOUT
			gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer, production_after_suffix_machine);
			#endif
			break;
		}
		
		case t_asterisk:
		{
			TODO;
			#if 0
			gegex_add_lambda_transition(retval.end,retval.start);
			gegex_add_lambda_transition(retval.start, retval.end);
			
			#ifdef DOTOUT
			gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer, production_after_suffix_machine);
			#endif
			break;
		}
		
		case t_qmark:
		{
			TODO;
			#if 0
			gegex_add_lambda_transition(retval.start, retval.end);
			
			#ifdef DOTOUT
			gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer, production_after_suffix_machine);
			#endif
			break;
		}
		
		case t_ocurly:
			TODO;
			break;
		
		default:
			break;
	}
	
	EXIT;
	return retval;
}


















