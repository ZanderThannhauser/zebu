
#include <debug.h>

/*#include "regex/state/new.h"*/
#include <lex/regex/dfa_to_nfa.h>
#include <lex/regex/dotout.h>
#include <lex/regex/state/add_lambda_transition.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/expression/after_suffix.h"

#include "prefixes.h"
#include "suffixes.h"

struct rbundle read_suffixes_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope)
{
	ENTER;
	
	struct rbundle retval = read_prefixes_token_expression(tokenizer, scratchpad, scope);
	
	switch (tokenizer->token)
	{
		case t_qmark:
			TODO;
			break;
		
		case t_asterisk:
		{
			// convert into nfa:
			if (!retval.is_nfa)
				retval = regex_dfa_to_nfa(retval.dfa, scratchpad);
			
			regex_add_lambda_transition(retval.nfa.end, scratchpad, retval.nfa.start);
			regex_add_lambda_transition(retval.nfa.start, scratchpad, retval.nfa.end);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ expression_after_suffix_machine);
			
			#ifdef DEBUGGING
			regex_dotout(retval.nfa.start);
			#endif
			break;
		}
		
		case t_plus:
		{
			// convert into nfa:
			if (!retval.is_nfa)
				retval = regex_dfa_to_nfa(retval.dfa, scratchpad);
			
			regex_add_lambda_transition(retval.nfa.end, scratchpad, retval.nfa.start);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ expression_after_suffix_machine);
			
			#ifdef DEBUGGING
			regex_dotout(retval.nfa.start);
			#endif
			break;
		}
		
		case t_ocurly:
		{
			TODO;
			#if 0
			// repeated clones and concat
			// require accepting
			// nfa_to_dfa
			// simplify
			TODO;
			#endif
			break;
		}
		
		default:
			break;
	}
	
	EXIT;
	return retval;
}








