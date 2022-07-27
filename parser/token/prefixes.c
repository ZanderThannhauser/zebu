
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/expression/root.h"

#include <lex/regex/complement.h>

#include "highest.h"
#include "prefixes.h"

struct rbundle read_prefixes_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope)
{
	ENTER;
	
	if (tokenizer->token == t_emark)
	{
		read_token(tokenizer, expression_root_machine);
		
		struct rbundle inner = read_highest_token_expression(tokenizer, scratchpad, scope);
		
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
		
		regex_complement(machine);
		
		EXIT;
		return (struct rbundle) {
			.is_nfa = false,
			.dfa = machine,
		};
	}
	else
	{
		struct rbundle retval = read_highest_token_expression(tokenizer, scratchpad, scope);
		EXIT;
		return retval;
	}
	
}










