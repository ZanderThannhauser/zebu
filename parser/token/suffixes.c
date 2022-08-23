
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
	struct memory_arena* arena,
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip)
{
	ENTER;
	
	struct rbundle retval = read_prefixes_token_expression(arena, tokenizer, scope, token_skip);
	
	switch (tokenizer->token)
	{
		case t_qmark:
		{
			TODO;
			#if 0
			// convert into nfa:
			if (!retval.is_nfa)
				retval = regex_dfa_to_nfa(retval.dfa, arena);
			
			regex_add_lambda_transition(retval.nfa.start, arena, retval.nfa.end);
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ regex_after_suffix_machine);
			
			#ifdef DEBUGGING
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			#endif
			break;
		}
		
		case t_asterisk:
		{
			// convert into nfa:
			if (!retval.is_nfa)
				retval = regex_dfa_to_nfa(retval.dfa, arena);
			
			if (token_skip)
			{
				struct regex* cloned = regex_clone(token_skip, arena);
				
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
			
			#ifdef DEBUGGING
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			break;
		}
		
		case t_plus:
		{
			// convert into nfa:
			if (!retval.is_nfa)
				retval = regex_dfa_to_nfa(retval.dfa, arena);
			
			if (token_skip)
			{
				struct regex* cloned = regex_clone(token_skip, arena);
				
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
			
			#ifdef DEBUGGING
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			break;
		}
		
		case t_ocurly:
		{
			TODO;
			#if 0
			struct rbundle original;
			
			// convert into nfa:
			if (retval.is_nfa)
				original = retval;
			else
				original = regex_dfa_to_nfa(retval.dfa, arena);
			
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
			
			struct regex* start = new_regex(arena);
			
			struct regex* moving = start;
			
			unsigned i;
			for (i = 0; i < min; i++)
			{
				// new_start, new_end = clone();
				
				// moving -> new_start
				
				// moving = new_end
				TODO;
			}
			
			struct regex* end = new_regex(arena);
			
			regex_add_lambda_transition(moving, arena, end);
			
			for (; i < max; i++)
			{
				// new_start, new_end = clone();
				struct clone_nfa_bundle clone = regex_clone_nfa(arena,
					original.nfa.start, original.nfa.end);
				
				// moving -> new_start
				regex_add_lambda_transition(moving, arena, clone.start);
				
				// moving = new_end
				moving = clone.end;
				
				// moving -> end
				regex_add_lambda_transition(moving, arena, end);
			}
			
			retval.is_nfa = true;
			retval.nfa.start = start;
			retval.nfa.end = end;
			
			#ifdef DEBUGGING
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
			
			read_token(
				/* tokenizer: */ tokenizer,
				/* machine:   */ regex_after_suffix_machine);
			
			free_regex(original.nfa.start, arena);
			#endif
			break;
		}
		
		default:
			break;
	}
	
	EXIT;
	return retval;
}


















