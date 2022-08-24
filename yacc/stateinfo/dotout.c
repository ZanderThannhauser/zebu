
#ifdef DOTOUT

#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/tree_t.h>
#include <avl/search.h>

#include <yacc/gegex/state/struct.h>

#include <set/of_tokens/to_string.h>

#include <named/grammar/struct.h>

#include <misc/phase_counters.h>

#include "node/struct.h"

#include "struct.h"
#include "dotout.h"

static void helper(
	struct gegex* state,
	struct gegex* here,
	char* lookaheads,
	FILE* stream)
{
	if (state->phase != yacc_phase_counter)
	{
		state->phase = yacc_phase_counter;
		
		fprintf(stream, ""
			"\"%p_%u\" [" "\n"
				"shape = %s" "\n"
				"style = filled" "\n"
				"fillcolor = %s" "\n"
				"label = \"%s\"" "\n"
			"];"
		"", state, yacc_phase_counter,
		state->is_reduction_point ? "doublecircle" : "circle",
		state == here ? "grey" : "white",
		state->is_reduction_point ? lookaheads : "");
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct transition* const t = state->transitions.data[i];
			
			helper(t->to, here, lookaheads, stream);
			
			fprintf(stream, ""
				"\"%p_%u\" -> \"%p_%u\" [" "\n"
					"label = \"token #%u\"" "\n"
				"];" "\n"
			"", state, yacc_phase_counter, t->to, yacc_phase_counter, t->token);
		}
		
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct gtransition* const t = state->grammar_transitions.data[i];
			
			helper(t->to, here, lookaheads, stream);
			
			fprintf(stream, ""
				"\"%p_%u\" -> \"%p_%u\" [" "\n"
					"label = \"%s\"" "\n"
				"];" "\n"
			"", state, yacc_phase_counter, t->to, yacc_phase_counter, t->grammar);
		}
		
		assert(!state->lambda_transitions.n);
	}
}

void yacc_stateinfo_dotout(
	struct yacc_stateinfo* this,
	struct avl_tree_t* new_grammar,
	FILE* stream)
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct yacc_stateinfo_node* tnode = node->item;
		
		struct avl_node_t* node = avl_search(new_grammar, &tnode->grammar);
		
		assert(node);
		
		struct named_grammar* ng = node->item;
		
		char* lookaheads = tokenset_to_string(tnode->lookaheads);
		
		yacc_phase_counter++;
		
		helper(ng->grammar, tnode->state, lookaheads, stream);
		
		free(lookaheads);
	}
	
	EXIT;
}

#endif


















