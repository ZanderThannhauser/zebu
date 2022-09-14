
#include <assert.h>

#include <debug.h>

#include <regex/dfa_to_nfa.h>
#include <regex/dotout.h>
#include <regex/clone.h>
#include <regex/state/add_lambda_transition.h>

#include "../tokenizer/struct.h"

#include "1.suffixes.h"
#include "2.concat.h"

struct rbundle read_concat_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope
) {
	ENTER;
	
	struct rbundle retval = read_suffixes_token_expression(tokenizer, scope);
	
	switch (tokenizer->token)
	{
		case t_oparen:
		case t_osquare:
		case t_identifier:
		case t_string_literal:
		case t_character_literal:
		case t_dot:
		{
			struct rbundle next = read_concat_token_expression(tokenizer, scope);
			
			if (!retval.is_nfa)
			{
				retval = regex_dfa_to_nfa(retval.dfa);
			}
			
			if (!next.is_nfa)
			{
				next = regex_dfa_to_nfa(next.dfa);
			}
			
			regex_add_lambda_transition(retval.nfa.end, next.nfa.start);
			
			#ifdef DOTOUT
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			
			retval = (struct rbundle) {
				.is_nfa = true,
				.nfa.start = retval.nfa.start,
				.nfa.end = next.nfa.end,
			};
			break;
		}
		
		case t_gravemark:
		case t_cparen:
		case t_ampersand:
		case t_vertical_bar:
		case t_semicolon:
		case t_colon:
			break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return retval;
}




















