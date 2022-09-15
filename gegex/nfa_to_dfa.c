
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <string/compare.h>
#include <string/are_equal.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/search.h>
#include <avl/free_tree.h>

#include <heap/new.h>
#include <heap/push.h>
#include <heap/len.h>
#include <heap/head.h>
#include <heap/pop.h>
#include <heap/free.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/len.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/unsigned/new.h>
#include <set/unsigned/update.h>
#include <set/unsigned/free.h>

#include <set/gegex/new.h>
#include <set/gegex/add.h>
#include <set/gegex/foreach.h>
#include <set/gegex/compare.h>
#include <set/gegex/free.h>

#include <gegex/state/struct.h>
#include <gegex/state/new.h>
#include <gegex/state/add_transition.h>
#include <gegex/state/add_grammar_transition.h>
/*#include <gegex/dotout.h>*/

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/update.h>
#include <yacc/structinfo/free.h>

#ifdef VERBOSE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <misc/default_sighandler.h>
#endif

#ifdef DOTOUT
#include "dotout.h"
#endif

#include "nfa_to_dfa.h"

struct mapping
{
	struct gegexset* stateset; // must be the first
	struct gegex* combined_state;
};

static struct mapping* new_mapping(
	struct gegexset* stateset,
	struct gegex* state)
{
	ENTER;
	
	struct mapping* this = smalloc(sizeof(*this));
	
	this->stateset = stateset;
	
	this->combined_state = state;
	
	EXIT;
	return this;
}

static int compare_mappings(const void* a, const void* b)
{
	const struct mapping *A = a, *B = b;
	return compare_gegexsets(A->stateset, B->stateset);
}

static void free_mapping(void* a)
{
	struct mapping* this = a;
	ENTER;
	
	free_gegexset(this->stateset);
	free(this);
	
	EXIT;
}

static void add_lambda_states(struct gegexset* set, struct gegex* ele)
{
	ENTER;
	
	if (gegexset_add(set, ele))
	{
		for (unsigned i = 0, n = ele->lambda_transitions.n; i < n; i++)
		{
			add_lambda_states(set, ele->lambda_transitions.data[i]);
		}
	}
	
	EXIT;
}

struct gegex* gegex_nfa_to_dfa(struct gegex* original_start)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	
	struct gegex* new_start = new_gegex();
	
	{
		struct gegexset* start_set = new_gegexset();
		
		add_lambda_states(start_set, original_start);
		
		struct mapping* mapping = new_mapping(start_set, new_start);
		
		quack_append(todo, mapping);
		
		avl_insert(mappings, mapping);
	}
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + quack_len(todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "zebu: grammar nfa-to-dfa: %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler);
	#endif
	
	#ifdef DOTOUT
	gegex_dotout(new_start, NULL, __PRETTY_FUNCTION__);
	#endif
	
	while (quack_len(todo))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct mapping* mapping = quack_pop(todo);
		
		struct gegexset* const stateset = mapping->stateset;
		
		struct gegex* const state = mapping->combined_state;
		
		// set this as reduction_point if any states in list are accepting:
		{
			bool is_reduction_point = false;
			
			gegexset_foreach(stateset, ({
				void runme(struct gegex* ele) {
					if (ele->is_reduction_point) {
						is_reduction_point = true;
					}
				}
				runme;
			}));
			
			state->is_reduction_point = is_reduction_point;
			
			dpvb(state->is_reduction_point);
		}
		
		// iterators for gegex_transitions:
		{
			struct iterator
			{
				struct gegex_transition **i, **n;
			};
			
			struct iterator* new_iterator(struct gegex* state)
			{
				ENTER;
				
				struct iterator* this = smalloc(sizeof(*this));
				
				this->i = state->transitions.data;
				
				this->n = state->transitions.data + state->transitions.n;
				
				EXIT;
				return this;
			}
			
			int compare_iterators(const void* a, const void* b)
			{
				const struct iterator* A = a, *B = b;
				
				unsigned token_a = A->i[0]->token;
				unsigned token_b = B->i[0]->token;
				
				if (token_a > token_b)
					return +1;
				else if (token_a < token_b)
					return -1;
				else
					return 0;
			}
			
			struct heap* heap = new_heap(compare_iterators);
			
			// create iterators for each state:
			gegexset_foreach(stateset, ({
				void runme(struct gegex* ele)
				{
					if (ele->transitions.n)
					{
						struct iterator* iter = new_iterator(ele);
						heap_push(heap, iter);
					}
				}
				runme;
			}));
			
			while (heap_len(heap))
			{
				struct iterator* iterator = heap_head(heap);
				
				struct gegex_transition* transition = iterator->i[0];
				
				unsigned min_token = transition->token;
				
				struct unsignedset* whitespace = new_unsignedset();
				
				struct gegexset* subgegexset = new_gegexset();
				
				struct structinfo* structinfo = new_structinfo(/* name: */ NULL);
				
				do
				{
					heap_pop(heap);
					
					add_lambda_states(subgegexset, transition->to);
					
					unsignedset_update(whitespace, transition->whitespace);
					
					structinfo_update(structinfo, transition->structinfo);
					
					if (++iterator->i < iterator->n)
						heap_push(heap, iterator);
					else
						free(iterator);
				}
				while (heap_len(heap) && (transition = (iterator = heap_head(heap))->i[0])->token == min_token);
				
				struct avl_node_t* node = avl_search(mappings, &subgegexset);
				
				if (node)
				{
					struct mapping* old = node->item;
					
					gegex_add_transition(state, min_token, whitespace, structinfo, old->combined_state);
					
					free_gegexset(subgegexset);
				}
				else
				{
					struct gegex* substate = new_gegex();
					
					struct mapping* new = new_mapping(subgegexset, substate);
					
					gegex_add_transition(state, min_token, whitespace, structinfo, substate);
					
					quack_append(todo, new);
					
					avl_insert(mappings, new);
				}
				
				free_structinfo(structinfo), free_unsignedset(whitespace);
			}
			
			free_heap(heap);
		}
		
		// iterators for gegex_grammar_transition:
		{
			struct iterator
			{
				struct gegex_grammar_transition **i, **n;
			};
			
			struct iterator* new_iterator(struct gegex* state)
			{
				ENTER;
				
				struct iterator* this = smalloc(sizeof(*this));
				
				this->i = state->grammar_transitions.data;
				
				this->n = state->grammar_transitions.data + state->grammar_transitions.n;
				
				EXIT;
				return this;
			}
			
			int compare_iterators(const void* a, const void* b)
			{
				const struct iterator* A = a, *B = b;
				
				struct string* grammar_a = A->i[0]->grammar;
				struct string* grammar_b = B->i[0]->grammar;
				
				return compare_strings(grammar_a, grammar_b);
			}
			
			struct heap* heap = new_heap(compare_iterators);
			
			// create iterators for each state:
			gegexset_foreach(stateset, ({
				void runme(struct gegex* ele)
				{
					if (ele->grammar_transitions.n)
					{
						struct iterator* iter = new_iterator(ele);
						heap_push(heap, iter);
					}
				}
				runme;
			}));
			
			while (heap_len(heap))
			{
				struct iterator* iterator;
				
				struct gegex_grammar_transition* transition;
				
				struct string* min_grammar = (transition = (iterator = heap_head(heap))->i[0])->grammar;
				
				struct gegexset* subgegexset = new_gegexset();
				
				struct structinfo* structinfo = new_structinfo(/* name: */ NULL);
				
				while (heap_len(heap) && strings_are_equal((transition = (iterator = heap_head(heap))->i[0])->grammar, min_grammar))
				{
					heap_pop(heap);
					
					add_lambda_states(subgegexset, transition->to);
					
					structinfo_update(structinfo, transition->structinfo);
					
					if (++iterator->i < iterator->n)
						heap_push(heap, iterator);
					else
						free(iterator);
				}
				
				struct avl_node_t* node = avl_search(mappings, &subgegexset);
				
				if (node)
				{
					struct mapping* old = node->item;
					
					gegex_add_grammar_transition(state, min_grammar, structinfo, old->combined_state);
					
					free_gegexset(subgegexset);
				}
				else
				{
					struct gegex* substate = new_gegex();
					
					struct mapping* new = new_mapping(subgegexset, substate);
					
					gegex_add_grammar_transition(state, min_grammar, structinfo, substate);
					
					quack_append(todo, new);
					
					avl_insert(mappings, new);
				}
				
				free_structinfo(structinfo);
			}
			
			free_heap(heap);
		}
		
		#ifdef DOTOUT
		gegex_dotout(new_start, NULL, __PRETTY_FUNCTION__);
		#endif
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	avl_free_tree(mappings);
	
	free_quack(todo);
	
	EXIT;
	return new_start;
}






















