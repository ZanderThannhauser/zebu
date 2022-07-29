

#include <assert.h>

#include <debug.h>

#include <lex/phase_counter.h>

#include "../state/struct.h"

#include "regex_ll/add.h"

#include "survey.h"

void simplify_dfa_survey(
	struct regex_ll* unique_nodes,
	struct regex* node)
{
	ENTER;
	
	dpv(node);
	
	if (node->phase != lex_phase_counter)
	{
		size_t i, n;
		
		node->phase = lex_phase_counter;
		
		assert(!node->lambda_transitions.n);
		
		for (i = 0, n = node->transitions.n; i < n; i++)
		{
			dpv(node->transitions.data[i]->value);
			simplify_dfa_survey(unique_nodes, node->transitions.data[i]->to);
		}
		
		if (node->default_transition_to)
			simplify_dfa_survey(unique_nodes, node->default_transition_to);
		
		// EOF transitions?
		if (node->EOF_transition_to)
			simplify_dfa_survey(unique_nodes, node->EOF_transition_to);
		
		regex_ll_add(unique_nodes, node);
	}
	
	EXIT;
}










