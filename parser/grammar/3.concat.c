
#include <assert.h>

#include <debug.h>

#include <gegex/add_lambda_transition.h>
#include <gegex/dotout.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/token_names.h"

#include "2.subdefinitions.h"
#include "3.concat.h"

struct gbundle read_concat_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle left = read_subdefinitions_production(tokenizer, scope, lex);
	
	again: switch (tokenizer->token)
	{
		case t_string_literal:
		case t_character_literal:
		case t_oparen:
		case t_identifier:
		case t_gravemark:
		case t_osquare:
		{
			struct gbundle right = read_concat_production(tokenizer, scope, lex);
			
			gegex_add_lambda_transition(left.accepts, right.start);
			
			#ifdef DOTOUT
			gegex_dotout(left.start, right.accepts, __PRETTY_FUNCTION__);
			#endif
			
			left = (struct gbundle) {left.start, right.accepts};
			goto again;
		}
		
		case t_vbar:
		case t_semicolon:
		case t_cparen:
		case t_colon:
			break;
		
		default:
		{
			dpv(tokenizer->token);
			dpvs(token_names[tokenizer->token]);
			TODO;
			break;
		}
	}
	
	EXIT;
	return left;
}




















