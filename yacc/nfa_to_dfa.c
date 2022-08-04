
#include <string.h>

#include <assert.h>

#include <memory/smalloc.h>
#include <stdlib.h>

#include <debug.h>

#include <yacc/gegex/state/struct.h>

#include <yacc/state/add_transition.h>
#include <yacc/state/add_reduce_transition.h>
#include <yacc/state/add_grammar_transition.h>

#include <avl/new.h>
#include <avl/search.h>
#include <avl/free_tree.h>
#include <avl/safe_insert.h>

#include <lex/build_tokenizer/build_tokenizer.h>

#include <set/of_gegexes/struct.h>
#include <set/of_gegexes/new.h>
#include <set/of_gegexes/clear.h>
#include <set/of_gegexes/free.h>
#include <set/of_gegexes/contains.h>
#include <set/of_gegexes/foreach.h>
#include <set/of_gegexes/add.h>
#include <set/of_gegexes/clone.h>
#include <set/of_gegexes/update.h>
#include <set/of_gegexes/compare.h>

#include <set/of_tokens/struct.h>
#include <set/of_tokens/new.h>
#include <set/of_tokens/add.h>
#include <set/of_tokens/foreach.h>
#include <set/of_tokens/free.h>

#ifdef DEBUGGING
#include <set/of_tokensets/struct.h>
#endif

#include <set/of_tokensets/foreach.h>
#include <set/of_tokensets/prettyprint.h>

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
	const struct gegexset* source_states,
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
	const struct cache_node* A = a, *B = b;
	return compare_gegexsets(A->source_states, B->source_states);
}

static void free_cache_node(void* a)
{
	struct cache_node* const this = a;
	ENTER;
	
	free_gegexset(this->source_states);
	free(this);
	
	EXIT;
}

struct shift_node
{
	unsigned token; // must be the first
	struct gegexset* destinations; // "owned" by struct
};

static struct shift_node* new_shift_node(unsigned token)
{
	ENTER;
	
	struct shift_node* this = smalloc(sizeof(*this));
	
	this->token = token;
	this->destinations = new_gegexset();
	
	EXIT;
	return this;
}

static void add_shift(
	struct avl_tree_t* tree,
	unsigned token,
	struct gegex* destination)
{
	ENTER;
	
	dpv(token);
	
	struct avl_node_t* node = avl_search(tree, &token);
	
	if (node)
	{
		struct shift_node* old = node->item;
		
		add_lambda_states(old->destinations, destination);
	}
	else
	{
		struct shift_node* new = new_shift_node(token);
		
		add_lambda_states(new->destinations, destination);
		
		safe_avl_insert(tree, new);
	}
	
	EXIT;
}

static int compare_shift_nodes(const void* a, const void* b)
{
	int cmp = 0;
	
	const struct shift_node* A = a, *B = b;
	
	if (A->token > B->token)
		cmp = +1;
	else if (A->token < B->token)
		cmp = -1;
	
	return cmp;
}

static void free_shift_node(void* ptr)
{
	ENTER;
	struct shift_node* this = ptr;
	free_gegexset(this->destinations);
	free(this);
	EXIT;
}

struct reduce_node
{
	unsigned token; // must be the first
	const char* grammar;
	unsigned popcount;
};

static struct reduce_node* new_reduce_node(
	unsigned token,
	const char* grammar,
	unsigned popcount)
{
	ENTER;
	
	struct reduce_node* this = smalloc(sizeof(*this));
	
	this->token = token;
	this->grammar = grammar;
	this->popcount = popcount;
	
	dpv(this->token);
	dpvs(this->grammar);
	dpv(this->popcount);
	
	EXIT;
	return this;
}

static void add_reduce(
	struct avl_tree_t* tree,
	unsigned token,
	const char* grammar,
	unsigned popcount)
{
	ENTER;
	
	dpv(token);
	
	struct avl_node_t* node = avl_search(tree, &token);
	
	if (node)
	{
		dpvs(grammar);
		TODO;
	}
	else
	{
		struct reduce_node* new = new_reduce_node(token, grammar, popcount);
		
		safe_avl_insert(tree, new);
	}
	
	EXIT;
}

static int compare_reduce_nodes(const void* a, const void* b)
{
	const struct reduce_node* A = a, *B = b;
	
	if (A->token > B->token)
		return +1;
	else if (A->token < B->token)
		return -1;
	else
		return +0;
}

static void free_reduce_node(void* ptr)
{
	ENTER;
	
	struct reduce_node* this = ptr;
	
	free(this);
	
	EXIT;
}

struct subgrammar_node
{
	const char* grammar;
	struct gegexset* destinations; // free me
};

static struct subgrammar_node* new_subgrammar_node(const char* grammar)
{
	ENTER;
	
	struct subgrammar_node* this = smalloc(sizeof(*this));
	
	this->grammar = grammar;
	this->destinations = new_gegexset();
	
	dpvs(this->grammar);
	
	EXIT;
	return this;
}

static void add_subgrammar(
	struct avl_tree_t* tree,
	const char* grammar,
	struct gegex* destination)
{
	ENTER;
	
	dpvs(grammar);
	
	struct avl_node_t* node = avl_search(tree, &grammar);
	
	if (node)
	{
		struct subgrammar_node* old = node->item;
		
		add_lambda_states(old->destinations, destination);
	}
	else
	{
		struct subgrammar_node* new = new_subgrammar_node(grammar);
		
		add_lambda_states(new->destinations, destination);
		
		safe_avl_insert(tree, new);
	}
	
	EXIT;
}

static int compare_subgrammar_nodes(const void* a, const void* b)
{
	const struct subgrammar_node* A = a, *B = b;
	
	return strcmp(A->grammar, B->grammar);
}

static void free_subgrammar_node(void* ptr)
{
	ENTER;
	
	struct subgrammar_node* this = ptr;
	
	free_gegexset(this->destinations);
	
	free(this);
	
	EXIT;
}

static struct yacc_state* helper(
	struct lex* lex,
	struct avl_tree_t* cache,
	struct memory_arena* scratchpad,
	const struct gegexset* source_states)
{
	struct yacc_state* state;
	ENTER;
	
	// lookup source_states in cache:
	struct avl_node_t* node = avl_search(cache, &source_states);
	
	if (node)
	{
		struct cache_node* cache = node->item;
		state = cache->state;
	}
	else
	{
		// create set for all tokens accepted by all gegex states:
		struct tokenset* all_tokens = new_tokenset();
		
		// map from token to set of gegex states:
		struct avl_tree_t* shift_tokens = new_avl_tree(compare_shift_nodes, free_shift_node);
		
		// map from token to name to reduce by:
		struct avl_tree_t* reduce_tokens = new_avl_tree(compare_reduce_nodes, free_reduce_node);
		
		// map from subgrammar name to set of gegex states:
		struct avl_tree_t* subgrammars = new_avl_tree(compare_subgrammar_nodes, free_subgrammar_node);
		
		// fill in the above sets:
		gegexset_foreach(source_states, ({
			void runme(struct gegex* state)
			{
				ENTER;
				dpv(state);
				
				unsigned i, n;
				
				dpv(state->transitions.n);
				
				for (i = 0, n = state->transitions.n; i < n; i++)
				{
					const struct transition* const ele = state->transitions.data[i];
					
					unsigned token = ele->token;
					
					add_shift(shift_tokens, token, ele->to);
					
					tokenset_add(all_tokens, token);
				}
				
				dpv(state->reduction_transitions.n);
				
				for (i = 0, n = state->reduction_transitions.n; i < n; i++)
				{
					const struct rtransition* const ele = state->reduction_transitions.data[i];
					
					unsigned token = ele->token;
					
					add_reduce(reduce_tokens, token, ele->reduce_as, ele->popcount);
					
					tokenset_add(all_tokens, token);
				}
				
				// grammar transitions
				dpv(state->grammar_transitions.n);
				for (i = 0, n = state->grammar_transitions.n; i < n; i++)
				{
					const struct gtransition* t = state->grammar_transitions.data[i];
					
					dpvs(t->grammar);
					
					add_subgrammar(subgrammars, t->grammar, t->to);
				}
				
				EXIT;
			}
			runme;
		}));
		
		// create and add new yacc_state to cache:
		state = new_yacc_state(scratchpad);
		
		safe_avl_insert(cache, new_cache_node(source_states, state));
		
		// don't free 'tokens', lex will do that
		struct tokensetset* tokens = lex_build_tokenzer(
			/* (   out) struct lex_state* start: */ &state->tokenizer_start,
			/* (in/out) struct lex* lex:         */ lex,
			/* (in/out) struct memory_arena*     */ scratchpad,
			/* (in)     struct tokenset* tokens: */ all_tokens);
		
		struct gegexset* substates = new_gegexset();
		
		dpv(tokens->n);
		
		tokensetset_prettyprint(tokens);
		
		// CHECK_NTH(2);
		
		tokensetset_foreach(tokens, ({
			void runme(struct tokenset* ele)
			{
				unsigned first = ele->data[0];
				
				dpv(first);
				
				// is this a shift or a reduce transition?
				if (avl_search(shift_tokens, &first))
				{
					gegexset_clear(substates);
					
					tokenset_foreach(ele, ({
						void runme(unsigned token) {
							dpv(token);
							
							if (avl_search(reduce_tokens, &token))
							{
								TODO;
								exit(1);
							}
							
							struct avl_node_t* node = avl_search(shift_tokens, &token);
							assert(node);
							
							struct shift_node* shift = node->item;
							dpv(shift->destinations->n);
							gegexset_update(substates, shift->destinations);
						}
						runme;
					}));
					
					dpv(substates->n);
					
					// call myself for destinations
					struct yacc_state* substate = helper(lex, cache, scratchpad, substates);
					
					// add transition
					yacc_state_add_transition(state, scratchpad, ele, substate);
				}
				else if (avl_search(reduce_tokens, &first))
				{
					const char* grammar = NULL;
					unsigned popcount;
					
					tokenset_foreach(ele, ({
						void runme(unsigned token) {
							dpv(token);
							
							if (avl_search(shift_tokens, &token))
							{
								TODO;
								exit(1);
							}
							
							struct avl_node_t* node = avl_search(reduce_tokens, &first);
							assert(node);
							
							struct reduce_node* reduce = node->item;
							
							dpvs(reduce->grammar);
							
							if (!grammar)
							{
								grammar = reduce->grammar;
								popcount = reduce->popcount;
							}
							else if (strcmp(grammar, reduce->grammar) || popcount != reduce->popcount)
							{
								TODO;
							}
						}
						runme;
					}));
					
					dpvs(grammar);
					assert(grammar);
					
					dpv(popcount);
					
					// add transition
					yacc_state_add_reduce_transition(state, scratchpad, ele, grammar, popcount);
				}
				else
				{
					// huh?
					TODO;
				}
			}
			runme;
		}));
		
		// grammar transitions
		for (struct avl_node_t* node = subgrammars->head; node; node = node->next)
		{
			struct subgrammar_node* ele = node->item;
			
			dpvs(ele->grammar);
			
			dpv(ele->destinations->n);
			
			assert(ele->destinations->n);
			
			// call myself for destinations
			struct yacc_state* substate = helper(lex, cache, scratchpad, ele->destinations);
			
			// add transition
			yacc_state_add_grammar_transition(state, scratchpad, ele->grammar, substate);
		}
		
		// cleanup
		free_tokenset(all_tokens);
		avl_free_tree(shift_tokens);
		avl_free_tree(reduce_tokens);
		avl_free_tree(subgrammars);
		free_gegexset(substates);
	}
	
	EXIT;
	return state;
}

struct yacc_state* yacc_nfa_to_dfa(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	struct avl_tree_t* cache = new_avl_tree(compare_cache_nodes, free_cache_node);
	
	struct avl_node_t* node = avl_search(grammar, (char*[]) {"(start)"});
	dpv(node);
	assert(node);
	
	struct named_grammar* start = node->item;
	dpv(start);
	
	struct gegexset* states = new_gegexset();
	
	add_lambda_states(states, start->grammar);
	
	struct yacc_state* new_start = helper(lex, cache, scratchpad, states);
	
	// cleanup and return
	avl_free_tree(cache);
	free_gegexset(states);
	
	EXIT;
	return new_start;
}



























