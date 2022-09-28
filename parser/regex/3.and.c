
#include <assert.h>

#include <debug.h>

#include <regex/struct.h>
#include <regex/free.h>
#include <regex/intersect_dfas.h>
#include <regex/nfa_to_dfa.h>
#include <regex/complement.h>
#include <regex/simplify_dfa.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "2.concat.h"
#include "3.and.h"

struct rbundle read_and_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct rbundle left = read_concat_token_expression(tokenizer, scope);
	
	while (tokenizer->token == t_ampersand)
	{
		read_token(tokenizer);
		
		bool take_complement = false;
		
		while (tokenizer->token == t_emark)
		{
			take_complement = !take_complement;
			read_token(tokenizer);
		}
		
		struct rbundle right = read_concat_token_expression(tokenizer, scope);
		
		struct regex* left_machine, *right_machine;
		
		if (left.accepts)
		{
			struct regex* dfa = regex_nfa_to_dfa(left);
			
			left_machine = regex_simplify_dfa(dfa);
			
			free_regex(left.start), free_regex(dfa);
		}
		else
		{
			left_machine = left.start;
		}
		
		if (right.accepts)
		{
			struct regex* dfa = regex_nfa_to_dfa(right);
			
			right_machine = regex_simplify_dfa(dfa);
			
			free_regex(right.start), free_regex(dfa);
		}
		else
		{
			right_machine = right.start;
		}
		
		if (take_complement)
			regex_complement(right_machine);
		
		struct regex* intersected = regex_intersect_dfas(left_machine, right_machine);
		
		struct regex* outgoing = regex_simplify_dfa(intersected);
		
		free_regex(left_machine), free_regex(right_machine);
		free_regex(intersected);
		
		left = (struct rbundle) {outgoing, NULL};
	}
	
	EXIT;
	return left;
}


























