
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
			
			if (!left.accepts)
				left = regex_dfa_to_nfa(left.start);
			
			if (!right.accepts)
				right = regex_dfa_to_nfa(right.start);
			
			regex_add_lambda_transition(left.accepts, right.start);
			
			#ifdef DOTOUT
			regex_dotout(left.start, __PRETTY_FUNCTION__);
			#endif
			
			left = (struct rbundle) {left.start, right.accepts};
			goto again;
		}
		
		case t_gravemark:
		case t_cparen:
		case t_ampersand:
		case t_vbar:
		case t_semicolon:
		case t_colon:
		case t_EOF:
		case t_error:
		case t_plus:
		case t_comma:
		case t_minus:
		case t_emark:
		case t_qmark:
		case t_caret:
		case t_percent:
		case t_asterisk:
		case t_csquare:
		case t_ocurly:
		case t_ccurly:
		case t_absolute_path:
		case t_array_hashtag:
		case t_scalar_hashtag:
		case number_of_tokens:
			break;
	}
	
	EXIT;
	return left;
}




















