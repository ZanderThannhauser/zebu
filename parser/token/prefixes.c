
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/regex/inside_emark.h"

#include <lex/regex/complement.h>

#include "highest.h"
#include "prefixes.h"

struct rbundle read_prefixes_token_expression(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip)
{
	ENTER;
	
	if (tokenizer->token == t_emark)
	{
		read_token(tokenizer, regex_inside_emark_machine);
		
		#ifdef WITH_ARENAS
		struct rbundle inner = read_highest_token_expression(arena, tokenizer, scope, token_skip);
		#else
		struct rbundle inner = read_highest_token_expression(tokenizer, scope, token_skip);
		#endif
		
		struct regex* machine;
		
		if (inner.is_nfa)
		{
/*			right.nfa.end->is_accepting = true;*/
/*			*/
/*			struct regex* nfa = right.nfa.start;*/
/*			struct regex* dfa = regex_nfa_to_dfa(nfa, scratchpad);*/
/*			*/
/*			right_machine = regex_simplify_dfa(dfa, scratchpad);*/
/*			*/
/*			free_regex(nfa, scratchpad), free_regex(dfa, scratchpad);*/
			TODO;
		}
		else
		{
			machine = inner.dfa;
		}
		
		#ifdef WITH_ARENAS
		regex_complement(arena, machine);
		#else
		regex_complement(machine);
		#endif
		
		EXIT;
		return (struct rbundle) {
			.is_nfa = false,
			.dfa = machine,
		};
	}
	else
	{
		#ifdef WITH_ARENAS
		struct rbundle retval = read_highest_token_expression(arena, tokenizer, scope, token_skip);
		#else
		struct rbundle retval = read_highest_token_expression(tokenizer, scope, token_skip);
		#endif
		
		EXIT;
		return retval;
	}
}










