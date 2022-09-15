
#include <assert.h>

#include <debug.h>

#include <regex/state/struct.h>
#include <regex/state/free.h>
#include <regex/intersect_dfas.h>
#include <regex/nfa_to_dfa.h>
#include <regex/complement.h>
#include <regex/simplify_dfa/simplify_dfa.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/regex/inside_and.h"

#include "2.concat.h"
#include "3.and.h"

struct rbundle read_and_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope
) {
	ENTER;
	
	struct rbundle left = read_concat_token_expression(tokenizer, scope);
	
	while (tokenizer->token == t_ampersand)
	{
		read_token(tokenizer, regex_inside_and_machine);
		
		bool take_complement = false;
		while (tokenizer->token == t_emark)
		{
			take_complement = !take_complement;
			read_token(tokenizer, regex_inside_and_machine);
		}
		
		struct rbundle right = read_concat_token_expression(tokenizer, scope);
		
		struct regex* left_machine, *right_machine;
		
		if (left.is_nfa)
		{
			TODO;
		}
		else
		{
			left_machine = left.dfa;
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
		
		if (take_complement)
			regex_complement(right_machine);
		
		struct regex* intersected = regex_intersect_dfas(left_machine, right_machine);
		
		struct regex* outgoing = regex_simplify_dfa(intersected);
		
		free_regex(intersected);
		
		left = (struct rbundle) {
			.is_nfa = false,
			.dfa = outgoing,
		};
	}
	
	EXIT;
	return left;
}

























