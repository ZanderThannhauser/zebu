
#include <assert.h>

#include <debug.h>

#include <lex/regex/dfa_to_nfa.h>
#include <lex/regex/dotout.h>
#include <lex/regex/clone.h>
#include <lex/regex/state/add_lambda_transition.h>

#include "../tokenizer/struct.h"

#include "suffixes.h"
#include "concat.h"

struct rbundle read_concat_token_expression(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct rbundle retval = read_suffixes_token_expression(arena, tokenizer, scope, token_skip);
	#else
	struct rbundle retval = read_suffixes_token_expression(tokenizer, scope, token_skip);
	#endif
	
	switch (tokenizer->token)
	{
		case t_oparen:
		case t_osquare:
		case t_identifier:
		case t_string_literal:
		case t_character_literal:
		case t_dot:
		{
			#ifdef WITH_ARENAS
			struct rbundle next = read_concat_token_expression(arena, tokenizer, scope, token_skip);
			#else
			struct rbundle next = read_concat_token_expression(tokenizer, scope, token_skip);
			#endif
			
			if (!retval.is_nfa)
			{
				#ifdef WITH_ARENAS
				retval = regex_dfa_to_nfa(arena, retval.dfa);
				#else
				retval = regex_dfa_to_nfa(retval.dfa);
				#endif
			}
			
			if (!next.is_nfa)
			{
				#ifdef WITH_ARENAS
				next = regex_dfa_to_nfa(arena, next.dfa);
				#else
				next = regex_dfa_to_nfa(next.dfa);
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
				regex_add_lambda_transition(cloned, next.nfa.start);
			}
			else
			{
				regex_add_lambda_transition(retval.nfa.end, next.nfa.start);
			}
			
			retval = (struct rbundle) {
				.is_nfa = true,
				.nfa.start = retval.nfa.start,
				.nfa.end = next.nfa.end,
			};
			
			#ifdef DOTOUT
			regex_dotout(retval.nfa.start, __PRETTY_FUNCTION__);
			#endif
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





















