
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/regex/inside_and.h"

#include <lex/regex/state/struct.h>
#include <lex/regex/state/free.h>
#include <lex/regex/intersect_dfas/intersect_dfas.h>
#include <lex/regex/nfa_to_dfa/nfa_to_dfa.h>
#include <lex/regex/simplify_dfa/simplify_dfa.h>

#include "concat.h"
#include "and.h"

struct rbundle read_and_token_expression(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct rbundle retval = read_concat_token_expression(arena, tokenizer, scope, token_skip);
	#else
	struct rbundle retval = read_concat_token_expression(tokenizer, scope, token_skip);
	#endif
	
	while (tokenizer->token == t_ampersand)
	{
		read_token(tokenizer, regex_inside_and_machine);
		
		#ifdef WITH_ARENAS
		struct rbundle right = read_concat_token_expression(arena, tokenizer, scope, token_skip);
		#else
		struct rbundle right = read_concat_token_expression(tokenizer, scope, token_skip);
		#endif
		
		struct regex* left_machine;
		
		if (retval.is_nfa)
		{
			TODO;
		}
		else
		{
			left_machine = retval.dfa;
		}
		
		struct regex* right_machine;
		
		if (right.is_nfa)
		{
			right.nfa.end->is_accepting = true;
			
			struct regex* nfa = right.nfa.start;
			
			#ifdef WITH_ARENAS
			struct regex* dfa = regex_nfa_to_dfa(nfa, arena);
			right_machine = regex_simplify_dfa(dfa, arena);
			#else
			struct regex* dfa = regex_nfa_to_dfa(nfa);
			right_machine = regex_simplify_dfa(dfa);
			#endif
			
			free_regex(nfa), free_regex(dfa);
		}
		else
		{
			right_machine = right.dfa;
		}
		
		dpv(left_machine);
		dpv(right_machine);
		
		#ifdef WITH_ARENAS
		struct regex* intersected = regex_intersect_dfas(left_machine, right_machine, arena);
		#else
		struct regex* intersected = regex_intersect_dfas(left_machine, right_machine);
		#endif
		
		#ifdef WITH_ARENAS
		struct regex* outgoing = regex_simplify_dfa(intersected, arena);
		#else
		struct regex* outgoing = regex_simplify_dfa(intersected);
		#endif
		
		free_regex(intersected);
		
		retval = (struct rbundle) {
			.is_nfa = false,
			.dfa = outgoing,
		};
	}
	
	EXIT;
	return retval;
}

















