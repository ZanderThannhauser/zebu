
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/subroot.h"
#include "../tokenizer/machines/production/inside_subdefinitions.h"

#include "../options/struct.h"

#include "../scope/push.h"
#include "../scope/pop.h"

#include "../read_charset.h"
#include "../read_fragment.h"
#include "../read_grammar.h"

/*#include "gegex/state/add_lambda_transition.h"*/

#include "suffixes.h"
#include "subdefinitions.h"

struct gbundle read_subdefinitions_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
	ENTER;
	
	if (tokenizer->token == t_percent)
	{
		read_token(tokenizer, subroot_machine);
		
		scope_push(scope);
		
		while (tokenizer->token != t_colon)
		{
			switch (tokenizer->token)
			{
				case t_charset:
					read_charset(tokenizer, scope);
					break;
				
				case t_fragment:
					read_fragment(tokenizer, scratchpad, scope, options->token_skip);
					break;
				
				case t_identifier:
					read_grammar(tokenizer, scratchpad, options, scope, lex);
					break;
				
				default:
					TODO;
					break;
			}
			
			if (tokenizer->token == t_semicolon)
				read_token(tokenizer, subroot_machine);
		}
		
		// read production rule:
		read_token(tokenizer, production_inside_subdefinitions_machine);
		
		retval = read_suffixes_production(tokenizer, scratchpad, options, scope, lex);
		
		scope_pop(scope);
	}
	else
	{
		retval = read_suffixes_production(tokenizer, scratchpad, options, scope, lex);
	}
	
	EXIT;
	return retval;
}






