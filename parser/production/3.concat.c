
#include <assert.h>

#include <debug.h>

#include <gegex/state/add_lambda_transition.h>
#include <gegex/dotout.h>

#include "../tokenizer/struct.h"

#include "2.subdefinitions.h"
#include "3.concat.h"

struct gbundle read_concat_production(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle inner = read_subdefinitions_production(tokenizer, options, scope, lex);
	
	switch (tokenizer->token)
	{
		case t_string_literal:
		case t_character_literal:
		case t_oparen:
		case t_identifier:
		case t_gravemark:
		case t_osquare:
		{
			struct gbundle right = read_concat_production(tokenizer, options, scope, lex);
			
			gegex_add_lambda_transition(inner.end, right.start);
			
			#ifdef DOTOUT
			gegex_dotout(inner.start, right.end, __PRETTY_FUNCTION__);
			#endif
			
			EXIT;
			return (struct gbundle) {inner.start, right.end};
		}
		
		case t_semicolon:
		case t_vertical_bar:
		case t_cparen:
		case t_colon:
			EXIT;
			return inner;
		
		default:
			TODO;
			break;
	}
}




















