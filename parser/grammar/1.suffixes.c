
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
			gegex_add_lambda_transition(retval.accepts, retval.start);
			
			#ifdef DOTOUT
			gegex_dotout(retval.start, retval.accepts, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer);
			break;
		}
		
		case t_asterisk:
		{
			gegex_add_lambda_transition(retval.accepts, retval.start);
			gegex_add_lambda_transition(retval.start, retval.accepts);
			
			#ifdef DOTOUT
			gegex_dotout(retval.start, retval.accepts, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer);
			break;
		}
		
		case t_qmark:
		{
			gegex_add_lambda_transition(retval.start, retval.accepts);
			
			#ifdef DOTOUT
			gegex_dotout(retval.start, retval.accepts, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer);
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


















