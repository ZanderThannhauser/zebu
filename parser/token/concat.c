
#include <assert.h>

#include <debug.h>

#include <lex/regex/dfa_to_nfa.h>
#include <lex/regex/dotout.h>
#include <lex/regex/state/add_lambda_transition.h>

#include "../tokenizer/struct.h"

#include "suffixes.h"
#include "concat.h"

struct rbundle read_concat_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope)
{
	ENTER;
	
	struct rbundle retval = read_suffixes_token_expression(tokenizer, scratchpad, scope);
	
	switch (tokenizer->token)
	{
		case t_oparen:
		case t_osquare:
		case t_identifier:
		case t_string_literal:
		case t_character_literal:
		case t_dot:
		{
			struct rbundle next = read_concat_token_expression(tokenizer, scratchpad, scope);
			
			if (!retval.is_nfa)
				retval = regex_dfa_to_nfa(retval.dfa, scratchpad);
			
			if (!next.is_nfa)
				next = regex_dfa_to_nfa(next.dfa, scratchpad);
			
			regex_add_lambda_transition(retval.nfa.end, scratchpad, next.nfa.start);
			
			retval = (struct rbundle) {
				.is_nfa = true,
				.nfa.start = retval.nfa.start,
				.nfa.end = next.nfa.end,
			};
			
			#ifdef DEBUGGING
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			break;
		}
		
		case t_gravemark:
		case t_cparen:
		case t_ampersand:
		case t_vertical_bar:
		case t_semicolon:
			break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return retval;
}





















