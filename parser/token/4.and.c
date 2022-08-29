
#include <assert.h>

#include <debug.h>

#include <lex/regex/state/struct.h>
#include <lex/regex/state/free.h>
#include <lex/regex/intersect_dfas.h>
#include <lex/regex/nfa_to_dfa.h>
#include <lex/regex/simplify_dfa/simplify_dfa.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/regex/inside_and.h"

#include "3.concat.h"
#include "4.and.h"

struct rbundle read_and_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip
) {
	ENTER;
	
	struct rbundle retval = read_concat_token_expression(tokenizer, scope, token_skip);
	
	while (tokenizer->token == t_ampersand)
	{
		read_token(tokenizer, regex_inside_and_machine);
		
		struct rbundle right = read_concat_token_expression(tokenizer, scope, token_skip);
		
		struct regex* left_machine, *right_machine;
		
		if (retval.is_nfa)
		{
			TODO;
		}
		else
		{
			left_machine = retval.dfa;
		}
		
		if (right.is_nfa)
		{
			right.nfa.end->is_accepting = true;
			
			struct regex* nfa = right.nfa.start;
			
			struct regex* dfa = regex_nfa_to_dfa(nfa);
			
			right_machine = regex_simplify_dfa(dfa);
			
			free_regex(nfa), free_regex(dfa);
		}
		else
		{
			right_machine = right.dfa;
		}
		
		dpv(left_machine);
		dpv(right_machine);
		
		struct regex* intersected = regex_intersect_dfas(left_machine, right_machine);
		
		struct regex* outgoing = regex_simplify_dfa(intersected);
		
		free_regex(intersected);
		
		retval = (struct rbundle) {
			.is_nfa = false,
			.dfa = outgoing,
		};
	}
	
	EXIT;
	return retval;
}
















