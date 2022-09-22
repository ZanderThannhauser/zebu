
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
		read_token(tokenizer);
		
		struct gbundle right = read_concat_production(tokenizer, scope, lex);
		
		gegex_add_lambda_transition(left.start, right.start);
		gegex_add_lambda_transition(right.accepts, left.accepts);
		
		#ifdef DOTOUT
		gegex_dotout(left.start, left.accepts, __PRETTY_FUNCTION__);
		#endif
	}
	
	EXIT;
	return left;
}










