
#include <assert.h>

#include <debug.h>

#include <regex/dfa_to_nfa.h>
#include <regex/dotout.h>
#include <regex/clone.h>
#include <regex/add_lambda_transition.h>

#include "../tokenizer/struct.h"

#include "1.suffixes.h"
#include "2.concat.h"

struct rbundle read_concat_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct rbundle left = read_suffixes_token_expression(tokenizer, scope);
	
	again: switch (tokenizer->token)
	{
		case t_oparen:
		case t_osquare:
		case t_identifier:
		case t_dot:
		case t_octal_literal:
		case t_string_literal:
		case t_decimal_literal:
		case t_character_literal:
		case t_hexadecimal_literal:
		{
			struct rbundle right = read_concat_token_expression(tokenizer, scope);
			
			if (!left.is_nfa)
			{
				left = regex_dfa_to_nfa(left.dfa);
			}
			
			if (!right.is_nfa)
			{
				right = regex_dfa_to_nfa(right.dfa);
			}
			
			regex_add_lambda_transition(left.nfa.accepts, right.nfa.start);
			
			#ifdef DOTOUT
			regex_dotout(left.nfa.start, __PRETTY_FUNCTION__);
			#endif
			
			left = (struct rbundle) {
				.is_nfa = true,
				.nfa.start = left.nfa.start,
				.nfa.accepts = right.nfa.accepts,
			};
			goto again;
		}
		
		case t_gravemark:
		case t_cparen:
		case t_ampersand:
		case t_vbar:
		case t_semicolon:
		case t_colon:
			break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return left;
}




















