
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

/*#include "regex/state/new.h"*/
#include <lex/regex/dfa_to_nfa.h>
#include <lex/regex/dotout.h>
#include <lex/regex/clone.h>
#include <lex/regex/state/new.h>
#include <lex/regex/state/free.h>
#include <lex/regex/state/add_lambda_transition.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/misc/numeric.h"
#include "../tokenizer/machines/misc/comma.h"
#include "../tokenizer/machines/misc/ccurly.h"
#include "../tokenizer/machines/regex/after_suffix.h"

#include "prefixes.h"
#include "suffixes.h"

struct rbundle read_suffixes_token_expression(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct rbundle retval = read_prefixes_token_expression(arena, tokenizer, scope, token_skip);
	#else
	struct rbundle retval = read_prefixes_token_expression(tokenizer, scope, token_skip);
	#endif
	
	switch (tokenizer->token)
	{
		case t_qmark:
		{
			// convert into nfa:
			if (!retval.is_nfa)
			{
				#ifdef WITH_ARENAS
				retval = regex_dfa_to_nfa(arena, retval.dfa);
				#else
				retval = regex_dfa_to_nfa(retval.dfa);
				#endif
			}
			
			regex_add_lambda_transition(retval.nfa.start, retval.nfa.end);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ regex_after_suffix_machine);
			
			#ifdef DOTOUT
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			break;
		}
		
		case t_asterisk:
		{
			// convert into nfa:
			if (!retval.is_nfa)
			{
				#ifdef WITH_ARENAS
				retval = regex_dfa_to_nfa(arena, retval.dfa);
				#else
				retval = regex_dfa_to_nfa(retval.dfa);
				#endif
			}
			
			if (token_skip)
			{
				#ifdef WITH_ARENAS
				struct regex* cloned = regex_clone(arena, token_skip);
				#else
				struct regex* cloned = regex_clone(token_skip);
				#endif
				
				regex_add_lambda_transition(retval.nfa.end, cloned);
				regex_add_lambda_transition(cloned, retval.nfa.start);
				regex_add_lambda_transition(retval.nfa.start, retval.nfa.end);
			}
			else
			{
				regex_add_lambda_transition(retval.nfa.end, retval.nfa.start);
				regex_add_lambda_transition(retval.nfa.start, retval.nfa.end);
			}
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ regex_after_suffix_machine);
			
			#ifdef DOTOUT
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			break;
		}
		
		case t_plus:
		{
			// convert into nfa:
			if (!retval.is_nfa)
			{
				#ifdef WITH_ARENAS
				retval = regex_dfa_to_nfa(arena, retval.dfa);
				#else
				retval = regex_dfa_to_nfa(retval.dfa);
				#endif
			}
			
			if (token_skip)
			{
				#ifdef WITH_ARENAS
				struct regex* cloned = regex_clone(arena, token_skip);
				#else
				struct regex* cloned = regex_clone(token_skip);
				#endif
				
				regex_add_lambda_transition(retval.nfa.end, cloned);
				regex_add_lambda_transition(cloned, retval.nfa.start);
			}
			else
			{
				regex_add_lambda_transition(retval.nfa.end, retval.nfa.start);
			}
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ regex_after_suffix_machine);
			
			#ifdef DOTOUT
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			break;
		}
		
		case t_ocurly:
		{
			struct rbundle original;
			
			// convert into nfa:
			if (retval.is_nfa)
				original = retval;
			else
			{
				#ifdef WITH_ARENAS
				original = regex_dfa_to_nfa(arena, retval.dfa);
				#else
				original = regex_dfa_to_nfa(retval.dfa);
				#endif
			}
			
			if (token_skip)
			{
				// oh boy...
				TODO;
			}
			
			read_token(tokenizer, numeric_machine);
			dpvs(tokenizer->tokenchars.chars);
			unsigned min = atoi(tokenizer->tokenchars.chars);
			dpv(min);
			
			read_token(tokenizer, comma_machine);
			
			read_token(tokenizer, numeric_machine);
			dpv(tokenizer->tokenchars.chars);
			unsigned max = atoi(tokenizer->tokenchars.chars);
			dpv(max);
			
			read_token(tokenizer, ccurly_machine);
			
			#ifdef WITH_ARENAS
			struct regex* start = new_regex(arena);
			#else
			struct regex* start = new_regex();
			#endif
			
			struct regex* moving = start;
			
			unsigned i;
			for (i = 0; i < min; i++)
			{
				// new_start, new_end = clone();
				
				// moving -> new_start
				
				// moving = new_end
				TODO;
			}
			
			#ifdef WITH_ARENAS
			struct regex* end = new_regex(arena);
			#else
			struct regex* end = new_regex();
			#endif
			
			regex_add_lambda_transition(moving, end);
			
			for (; i < max; i++)
			{
				// new_start, new_end = clone();
				#ifdef WITH_ARENAS
				struct clone_nfa_bundle clone = regex_clone_nfa(arena, original.nfa.start, original.nfa.end);
				#else
				struct clone_nfa_bundle clone = regex_clone_nfa(original.nfa.start, original.nfa.end);
				#endif
				
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
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ regex_after_suffix_machine);
			
			free_regex(original.nfa.start);
			break;
		}
		
		default:
			break;
	}
	
	EXIT;
	return retval;
}


















