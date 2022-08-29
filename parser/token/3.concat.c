
#include <assert.h>

#include <debug.h>

#include <lex/regex/dfa_to_nfa.h>
#include <lex/regex/dotout.h>
#include <lex/regex/clone.h>
#include <lex/regex/state/add_lambda_transition.h>

#include "../tokenizer/struct.h"

#include "2.suffixes.h"
#include "3.concat.h"

struct rbundle read_concat_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip
) {
	ENTER;
	
	struct rbundle retval = read_suffixes_token_expression(tokenizer, scope, token_skip);
	
	switch (tokenizer->token)
	{
		case t_oparen:
		case t_osquare:
		case t_identifier:
		case t_string_literal:
		case t_character_literal:
		case t_dot:
		{
			struct rbundle next = read_concat_token_expression(tokenizer, scope, token_skip);
			
			if (!retval.is_nfa)
			{
				retval = regex_dfa_to_nfa(retval.dfa);
			}
			
			if (!next.is_nfa)
			{
				next = regex_dfa_to_nfa(next.dfa);
			}
			
			if (token_skip)
			{
				struct regex* cloned = regex_clone(token_skip);
				
				regex_add_lambda_transition(retval.nfa.end, cloned);
				regex_add_lambda_transition(cloned, next.nfa.start);
			}
			else
			{
				regex_add_lambda_transition(retval.nfa.end, next.nfa.start);
			}
			
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




















