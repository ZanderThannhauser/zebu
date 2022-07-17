
#include <debug.h>

#include <yacc/gegex/state/struct.h>

#include <avl/new.h>
#include <avl/search.h>
#include <avl/safe_insert.h>

#include <lex/build_tokenizer/build_tokenizer.h>

#include <ptrset/new.h>
#include <ptrset/contains.h>
#include <ptrset/foreach.h>
#include <ptrset/add.h>
#include <ptrset/clone.h>

#include <tokenset/new.h>
#include <tokenset/add.h>
/*#include <tokenset/is_disjoint.h>*/

#include <named/grammar/struct.h>

#include "state/struct.h"
#include "state/new.h"

#include "nfa_to_dfa.h"

static void add_lambda_states(
	struct ptrset* outgoing,
	struct gegex* state)
{
	unsigned i, n;
	ENTER;
	
	if (!ptrset_contains(outgoing, state))
	{
		ptrset_add(outgoing, state);
		
		for (i = 0, n = state->lambda_transitions.n; i < n; i++)
			add_lambda_states(outgoing, state->lambda_transitions.data[i]);
	}
	
	EXIT;
}

struct cache_node
{
	struct ptrset* source_states; // should be freed
	struct yacc_state* state;
};

struct cache_node* new_cache_node(
	const struct ptrset* source_states,
	struct yacc_state* state)
{
	ENTER;
	
	struct ptrset* my_source_states = ptrset_clone(source_states);
	
	struct cache_node* this = smalloc(sizeof(*this));
	
	this->source_states = my_source_states;
	this->state = state;
	
	EXIT;
	return this;
}

static int compare_cache_nodes(const void* a, const void* b)
{
	TODO;
}

static void free_cache_node(void* a)
{
	TODO;
}

static struct yacc_state* helper(
	struct avl_tree_t* cache,
	struct memory_arena* scratchpad,
	const struct ptrset* source_states)
{
	ENTER;
	
	// lookup source_states in cache:
	struct avl_node_t* node = avl_search(cache, &source_states);
	
	if (node)
	{
		// return yacc state
		TODO;
	}
	else
	{
		// add new yacc_state to cache
		struct yacc_state* state = new_yacc_state(scratchpad);
		
		safe_avl_insert(cache, new_cache_node(source_states, state));
		
		struct tokenset* shift_tokens = new_tokenset();
		struct tokenset* reduce_tokens = new_tokenset();
		struct tokenset* all_tokens = new_tokenset();
		
		// make a set of all shift tokens, and a set of reduce tokens
		ptrset_foreach(source_states, ({
			void runme(const void* ptr)
			{
				unsigned i, n;
				const struct gegex* state = ptr;
				
				for (i = 0, n = state->transitions.n; i < n; i++)
				{
					unsigned token = state->transitions.data[i]->token;
					
					tokenset_add(shift_tokens, token);
					tokenset_add(all_tokens, token);
				}
				
				for (i = 0, n = state->reduction_transitions.n; i < n; i++)
				{
					unsigned token = state->reduction_transitions.data[i]->token;
					
					tokenset_add(reduce_tokens, token);
					tokenset_add(all_tokens, token);
				}
			}
			runme;
		}));
		
		// build a tokenizer (on the union), which returns a machine id
		// and a list of extra tokens (lex function to lookup source tokens?)
		state->tokenizer_start = lex_build_tokenzer(all_tokens);
		TODO;
		
		TODO;
		#if 0
		// add extra tokens to source-tokens' sets
		TODO;
		
		// make sure they're "disjoint"
		if (!tokenset_is_disjoint(shift_tokens, reduce_tokens))
		{
			TODO;
		}
		
		// add transitions in relevant states
		TODO;
		
		// for each token in shift tokens:
			// make a set of destinations
			// add_lambda_states
			// call self
			// add transition
		TODO;
		
		// for each token in reduce tokens:
			// check that all transitions for this token have the same reduction
			// add_lambda_states
			// call self
			// add transition
		TODO;
		
		// make a list of grammar iterators
		TODO;
		
		// while len(token iterators) > 0:
			// skim through list, finding minimum value and set of destinations
			TODO;
			
			// add_lambda_states for each
			TODO;
			
			// call self on set
			TODO;
			
			// add grammar transition 
			TODO;
		
		// cleanup
		TODO;
		#endif
	}
	
	EXIT;
}

struct gegex* yacc_nfa_to_dfa(
	struct avl_tree_t* grammar,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	struct avl_tree_t* cache = new_avl_tree(compare_cache_nodes, free_cache_node);
	
	struct avl_node_t* node = avl_search(grammar, (char*[]) {"(start)"});
	dpv(node);
	
	struct named_grammar* start = node->item;
	dpv(start);
	
	struct ptrset* states = new_ptrset();
	add_lambda_states(states, start->start);
	
	struct yacc_state* new_start = helper(cache, scratchpad, states);
	
	TODO;
	
	EXIT;
}



























