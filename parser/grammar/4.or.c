
#include <debug.h>

#include <gegex/add_lambda_transition.h>
#include <gegex/dotout.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "3.concat.h"
#include "4.or.h"

struct gbundle read_or_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle left = read_concat_production(tokenizer, scope, lex);
	
	while (tokenizer->token == t_vbar)
	{
		TODO;
		#if 0
		read_token(tokenizer, production_inside_or_machine);
		
		struct gbundle sub = read_concat_production(tokenizer, scope, lex);
		
		gegex_add_lambda_transition(retval.start, sub.start);
		
		gegex_add_lambda_transition(sub.end, retval.end);
		
		#ifdef DOTOUT
		gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
		#endif
		#endif
	}
	
	EXIT;
	return left;
}










