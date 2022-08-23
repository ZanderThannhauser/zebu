
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/production/inside_or.h"

#include <yacc/gegex/state/add_lambda_transition.h>
#include <yacc/gegex/dotout.h>

#include "concat.h"
#include "or.h"

struct gbundle read_or_production(
	#ifdef WITH_ARENAS
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	#endif
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle retval = read_concat_production(
		#ifdef WITH_ARENAS
		grammar_arena, token_arena,
		#endif
		tokenizer, options, scope, lex);
	
	while (tokenizer->token == t_vertical_bar)
	{
		read_token(tokenizer, production_inside_or_machine);
		
		struct gbundle sub = read_concat_production(
			#ifdef WITH_ARENAS
			grammar_arena, token_arena,
			#endif
			tokenizer, options, scope, lex);
		
		gegex_add_lambda_transition(retval.start, sub.start);
		
		gegex_add_lambda_transition(sub.end, retval.end);
		
		#ifdef DEBUGGING
		gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
		#endif
	}
	
	EXIT;
	return retval;
}

