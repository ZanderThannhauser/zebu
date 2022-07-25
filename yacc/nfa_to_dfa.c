
#include <debug.h>

#include <yacc/gegex/state/struct.h>

#include <avl/new.h>
#include <avl/search.h>
#include <avl/safe_insert.h>

#include <lex/build_tokenizer/build_tokenizer.h>

#include <set/of_gegexs/new.h>
#include <set/of_gegexs/contains.h>
#include <set/of_gegexs/foreach.h>
#include <set/of_gegexs/add.h>
#include <set/of_gegexs/clone.h>

#include <set/of_tokens/new.h>
#include <set/of_tokens/add.h>
/*#include <tokenset/is_disjoint.h>*/

#include <named/grammar/struct.h>

#include "state/struct.h"
#include "state/new.h"

#include "nfa_to_dfa.h"

static void add_lambda_states(
	struct gegexset* outgoing,
	struct gegex* state)
{
	unsigned i, n;
	ENTER;
	
	if (!gegexset_contains(outgoing, state))
	{
		gegexset_add(outgoing, state);
		
		for (i = 0, n = state->lambda_transitions.n; i < n; i++)
			add_lambda_states(outgoing, state->lambda_transitions.data[i]);
	}
	
	EXIT;
}

struct cache_node
{
	struct gegexset* source_states; // should be freed
	struct yacc_state* state;
};

static struct cache_node* new_cache_node(
	const struct ptrset* source_states,
	struct yacc_state* state)
{
	ENTER;
	
	struct gegexset* my_source_states = gegexset_clone(source_states);
	
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

struct shift_node
{
	unsigned token;
	struct gegexset* destinations;
};

static struct shift_node* new_shift_node()
{
	TODO;
}

static void add_shift()
{
	TODO;
}

static int compare_shift_nodes()
{
	TODO;
}

static void free_shift_node()
{
	TODO;
}

struct reduce_node
{
	unsigned token;
	char* grammar;
};

static struct reduce_node* new_reduce_node()
{
	TODO;
}

static void add_reduce()
{
	TODO;
}

static int compare_reduce_nodes()
{
	TODO;
}

static void free_reduce_node()
{
	TODO;
}

static struct yacc_state* helper(
	struct lex* lex,
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
		// create set for all tokens accepted by all gegex states:
		struct tokenset* all_tokens = new_tokenset();
		
		// map from token to set of gegex states:
		struct avl_tree_t* shift_tokens = new_avl_tree(compare_shift_nodes, free_shift_node);
		
		// map from token to name to reduce by:
		struct avl_tree_t* reduce_tokens = new_avl_tree(compare_reduce_nodes, free_reduce_node);
		
		// fill in the above sets:
		ptrset_foreach(source_states, ({
			void runme(const void* ptr)
			{
				unsigned i, n;
				const struct gegex* state = ptr;
				
				for (i = 0, n = state->transitions.n; i < n; i++)
				{
					unsigned token = state->transitions.data[i]->token;
					
					add_shift(shift_tokens, token,
						state->transitions.data[i]->next);
					
					tokenset_add(all_tokens, token);
				}
				
				for (i = 0, n = state->reduction_transitions.n; i < n; i++)
				{
					unsigned token = state->reduction_transitions.data[i]->token;
					
					add_reduce(reduce_tokens, token,
						state->reduction_transitions.data[i]->reduce_as);
					
					tokenset_add(all_tokens, token);
				}
			}
			runme;
		}));
		
		// create and add new yacc_state to cache:
		struct yacc_state* state = new_yacc_state(scratchpad);
		
		safe_avl_insert(cache, new_cache_node(source_states, state));
		
		struct tokensetset* tokens = lex_build_tokenzer(&state->tokenizer_start, lex, all_tokens);
		
		for (unsigned i = 0, n = tokens->n; i < n; i++)
		{
			const struct tokenset* ele = tokens->data[i];
			
			dpv(ele);
			dpv(ele->n);
			
			// if ele in shifts:
				// destinations = set();
				// for t in ele:
					// assert(t not in reduce)
					// destinations.update(shifts[t]);
				// call myself for destinations
				// add transition
			// else:
				// assert(ele in reduces);
				// add transition
				TODO;
		}
		
		// cleanup
		TODO;
	}
	
	EXIT;
}

struct gegex* yacc_nfa_to_dfa(
	struct lex* lex,
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
	
	struct yacc_state* new_start = helper(lex, cache, scratchpad, states);
	
	TODO;
	
	EXIT;
}



























