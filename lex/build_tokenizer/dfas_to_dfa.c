
#include <debug.h>

#include <assert.h>
#include <stdlib.h>

#include <arena/malloc.h>
#include <arena/dealloc.h>
#include <arena/calloc.h>

#include <avl/alloc_tree.h>
#include <avl/search.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <lex/regex/state/struct.h>
#include <lex/regex/dotout.h>

#include <lex/state/add_transition.h>
#include <lex/state/dotout.h>
#include <lex/state/struct.h>
#include <lex/state/set_default_transition.h>
#include <lex/state/set_EOF_transition.h>

#include <set/of_regexes/struct.h>
#include <set/of_regexes/new.h>
#include <set/of_regexes/add.h>
#include <set/of_regexes/clear.h>
#include <set/of_regexes/clone.h>
#include <set/of_regexes/free.h>
#include <set/of_regexes/foreach.h>
#include <set/of_regexes/compare.h>

#include <set/of_tokens/struct.h>
#include <set/of_tokens/new.h>
#include <set/of_tokens/add.h>
#include <set/of_tokens/clear.h>
#include <set/of_tokens/free.h>

#include <set/of_tokensets/add.h>

#include "../state/new.h"

#include "dfas_to_dfa.h"

struct dfas_to_dfa_node
{
	struct regexset* states; // must be first
	
	struct lex_state* result;
	
	struct memory_arena* arena;
};

static struct dfas_to_dfa_node* new_dfas_to_dfa_node(
	struct memory_arena* arena,
	const struct regexset* const original_states,
	struct lex_state* result)
{
	ENTER;
	
	struct dfas_to_dfa_node* node = arena_malloc(arena, sizeof(*node));
	
	node->states = regexset_clone(original_states, arena);
	node->result = result;
	
	node->arena = arena;
	
	EXIT;
	return node;
}

static int compare_dfas_to_dfa_nodes(
	const void* a, const void* b)
{
	int cmp = 0;
	const struct dfas_to_dfa_node* A = a, *B = b;
	
	cmp = compare_regexsets(A->states, B->states);
	
	return cmp;
}

static void free_dfas_to_dfa_node(void* ptr)
{
	struct dfas_to_dfa_node* const this = ptr;
	ENTER;
	
	free_regexset(this->states);
	
	arena_dealloc(this->arena, this);
	
	EXIT;
}

static struct lex_state* helper(
	struct memory_arena* arena,
	struct tokensetset* accepting,
	struct avl_tree_t* cache,
	struct regexset* states)
{
	struct lex_state* state;
	ENTER;
	
	struct avl_node_t* node = avl_search(cache, &states);
	
	if (node)
	{
		struct dfas_to_dfa_node* cached = node->item;
		assert(cached);
		state = cached->result;
	}
	else
	{
		state = new_lex_state(arena);
		
		avl_insert(cache, new_dfas_to_dfa_node(arena, states, state));
		
		// accepting?
		{
			struct tokenset* ts = new_tokenset(arena);
			unsigned prority;
			
			regexset_foreach(states, ({
				void runme(struct regex* ele) {
					if (ele->is_accepting)
					{
						if (!ts->n || prority < ele->priority)
						{
							prority = ele->priority;
							tokenset_clear(ts);
							tokenset_add(ts, ele->is_accepting);
						}
						else if (prority == ele->priority)
						{
							tokenset_add(ts, ele->is_accepting);
						}
					}
					
				}
				runme;
			}));
			
			if (ts->n)
			{
				struct tokenset* st;
				
				if ((st = tokensetset_add(accepting, ts)))
					state->accepting = st;
				else
					state->accepting = ts, ts = NULL;
			}
			
			free_tokenset(ts);
		}
		
		// merge transitions and sub-states:
		{
			unsigned *positions = arena_calloc(arena, states->n, sizeof(unsigned));
			
			unsigned value;
			struct regexset* subset = new_regexset(arena);
			
			while (({
				value = -1, regexset_clear(subset);
				
				for (unsigned i = 0, n = states->n; i < n; i++)
				{
					dpv(i);
					
					struct regex* ele = states->data[i];
					
					dpv(positions[i]);
					dpv(ele->transitions.n);
					
					unsigned pi = positions[i];
					if (pi < ele->transitions.n)
					{
						dpv(ele->transitions.data[pi]);
						
						unsigned evalue = ele->transitions.data[pi]->value;
						
						dpv(evalue);
						
						if (evalue < value)
						{
							dpv(ele->transitions.data[pi]->to);
							
							regexset_clear(subset);
							regexset_add(subset, ele->transitions.data[pi]->to);
							
							value = evalue;
						}
						else if (evalue == value)
						{
							dpv(ele->transitions.data[pi]->to);
							regexset_add(subset, ele->transitions.data[pi]->to);
						}
					}
				}
				
				dpv(subset->n);
				
				subset->n;
			}))
			{
				dpv(value);
				
				// call myself:
				struct lex_state* substate = helper(arena, accepting, cache, subset);
				
				// create new transition:
				lex_state_add_transition(state, value, substate);
				
				// move positions:
				for (unsigned i = 0, n = states->n; i < n; i++)
				{
					if (true
						&& positions[i] < states->data[i]->transitions.n
						&& states->data[i]->transitions.data[positions[i]]->value == value)
					{
						positions[i]++;
					}
				}
			}
			
			free_regexset(subset);
			arena_dealloc(arena, positions);
		}
		
		// handle default_transition_to:
		{
			struct regexset* rs = new_regexset(arena);
			
			regexset_foreach(states, ({
				void runme(struct regex* ele) {
					if (ele->default_transition_to) {
						regexset_add(rs, ele->default_transition_to);
					}
				}
				runme;
			}));
			
			if (rs->n)
			{
				// call myself:
				struct lex_state* substate = helper(arena, accepting, cache, rs);
				
				// create new transition:
				lex_state_set_default_transition(state, substate);
			}
			
			free_regexset(rs);
		}
		
		// handle EOF transitions:
		{
			struct regexset* rs = new_regexset(arena);
			
			regexset_foreach(states, ({
				void runme(struct regex* ele) {
					if (ele->EOF_transition_to) {
						regexset_add(rs, ele->EOF_transition_to);
					}
				}
				runme;
			}));
			
			if (rs->n)
			{
				// call myself:
				struct lex_state* substate = helper(arena, accepting, cache, rs);
				
				// create new transition:
				lex_state_set_EOF_transition(state, substate);
			}
			
			free_regexset(rs);
		}
	}
	
	EXIT;
	return state;
}

struct lex_state* dfas_to_dfa(
	struct memory_arena* arena,
	struct tokensetset* accepting,
	struct regexset* starts)
{
	ENTER;
	
	#ifdef DEBUGGING
	regex_dotout_set(starts);
	#endif
	
	struct avl_tree_t* cache = avl_alloc_tree(arena, compare_dfas_to_dfa_nodes, free_dfas_to_dfa_node);
	
	struct lex_state* new = helper(arena, accepting, cache, starts);
	
	#ifdef DEBUGGING
	lex_state_dotout(new);
	#endif
	
	avl_free_tree(cache);
	
	EXIT;
	return new;
}

















