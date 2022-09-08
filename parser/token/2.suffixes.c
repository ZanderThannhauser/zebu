
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

/*#include "regex/state/new.h"*/
#include <regex/dfa_to_nfa.h>
#include <regex/dotout.h>
#include <regex/clone.h>
#include <regex/state/new.h>
#include <regex/state/free.h>
#include <regex/state/add_lambda_transition.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/misc/numeric.h"
#include "../tokenizer/machines/misc/comma.h"
#include "../tokenizer/machines/misc/ccurly.h"
#include "../tokenizer/machines/regex/after_suffix.h"

#include "1.prefixes.h"
#include "2.suffixes.h"

struct rbundle read_suffixes_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope
) {
	ENTER;
	
	struct rbundle retval = read_prefixes_token_expression(tokenizer, scope);
	
	switch (tokenizer->token)
	{
		case t_qmark:
		{
			// convert into nfa:
			if (!retval.is_nfa)
			{
				retval = regex_dfa_to_nfa(retval.dfa);
			}
			
			regex_add_lambda_transition(retval.nfa.start, retval.nfa.end);
			
			#ifdef DOTOUT
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer, regex_after_suffix_machine);
			break;
		}
		
		case t_asterisk:
		{
			// convert into nfa:
			if (!retval.is_nfa)
			{
				retval = regex_dfa_to_nfa(retval.dfa);
			}
			
			regex_add_lambda_transition(retval.nfa.end, retval.nfa.start);
			regex_add_lambda_transition(retval.nfa.start, retval.nfa.end);
			
			#ifdef DOTOUT
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer, regex_after_suffix_machine);
			break;
		}
		
		case t_plus:
		{
			// convert into nfa:
			if (!retval.is_nfa)
			{
				retval = regex_dfa_to_nfa(retval.dfa);
			}
			
			regex_add_lambda_transition(retval.nfa.end, retval.nfa.start);
			
			#ifdef DOTOUT
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer, regex_after_suffix_machine);
			
			break;
		}
		
		case t_ocurly:
		{
			struct rbundle original;
			// convert into nfa:
			if (retval.is_nfa)
				original = retval;
			else
				original = regex_dfa_to_nfa(retval.dfa);
			
			read_token(tokenizer, numeric_machine);
			dpvs(tokenizer->tokenchars.chars);
			unsigned min = atoi((void*) tokenizer->tokenchars.chars);
			dpv(min);
			
			read_token(tokenizer, comma_machine);
			
			read_token(tokenizer, numeric_machine);
			dpv(tokenizer->tokenchars.chars);
			unsigned max = atoi((void*) tokenizer->tokenchars.chars);
			dpv(max);
			
			read_token(tokenizer, ccurly_machine);
			
			struct regex* start = new_regex();
			
			struct regex* moving = start;
			
			unsigned i;
			for (i = 0; i < min; i++)
			{
				// new_start, new_end = clone();
				
				// moving -> new_start
				
				// moving = new_end
				TODO;
			}
			
			struct regex* end = new_regex();
			
			regex_add_lambda_transition(moving, end);
			
			for (; i < max; i++)
			{
				// new_start, new_end = clone();
				struct clone_nfa_bundle clone = regex_clone_nfa(original.nfa.start, original.nfa.end);
				
				// moving -> new_start
				regex_add_lambda_transition(moving, clone.start);
				
				// moving = new_end
				moving = clone.end;
				
				// moving -> end
				regex_add_lambda_transition(moving, end);
			}
			
			retval.is_nfa = true;
			retval.nfa.start = start;
			retval.nfa.end = end;
			
			#ifdef DOTOUT
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			
			read_token(tokenizer, regex_after_suffix_machine);
			
			free_regex(original.nfa.start);
			break;
		}
		
		default:
			break;
	}
	
	EXIT;
	return retval;
}
















