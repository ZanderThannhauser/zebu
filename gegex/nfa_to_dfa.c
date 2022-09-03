
#include <debug.h>

#include <gegex/state/struct.h>
#include <gegex/state/new.h>
#include <gegex/state/add_transition.h>
#include <gegex/state/add_grammar_transition.h>
#include <gegex/dotout.h>

#include <set/string/new.h>
#include <set/string/add.h>
#include <set/string/foreach.h>
#include <set/string/update.h>

#include <set/gegex/new.h>
#include <set/gegex/add.h>
#include <set/gegex/foreach.h>
#include <set/gegex/compare.h>
#include <set/gegex/free.h>

#include <heap/struct.h>
#include <heap/len.h>
#include <heap/new.h>
#include <heap/push.h>
#include <heap/pop.h>
#include <heap/free.h>

#ifdef VERBOSE
#include <misc/default_sighandler.h>
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
			"\e[k" "%s: gegex nfa-to-dfa: %u of %u (%.2f%%)\r", argv0,
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
				struct iterator* iterator;
				
				struct gegex_transition* transition;
				
				unsigned min_token = (transition = (iterator = heap->data[0])->i[0])->token;
				
				dpv(min_token);
				
				struct gegexset* subgegexset = new_gegexset();
				
				struct stringset* tags = new_stringset();
				
				while (heap->n && (transition = (iterator = heap->data[0])->i[0])->token == min_token)
				{
					heap_pop(heap);
					
					add_lambda_states(subgegexset, transition->to);
					
					stringset_update(tags, transition->tags);
					
					if (++iterator->i < iterator->n)
						heap_push(heap, iterator);
					else
						free(iterator);
				}
				
				struct avl_node_t* node = avl_search(mappings, &subgegexset);
				
				if (node)
				{
					struct mapping* old = node->item;
					
					gegex_add_transition(state, min_token, tags, old->combined_state);
					
					free_gegexset(subgegexset);
				}
				else
				{
					struct gegex* substate = new_gegex();
					
					struct mapping* new = new_mapping(subgegexset, substate);
					
					gegex_add_transition(state, min_token, tags, substate);
					
					quack_append(todo, new);
					
					avl_insert(mappings, new);
				}
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
			
			while (heap->n)
			{
				struct iterator* iterator;
				
				struct gegex_grammar_transition* transition;
				
				struct string* min_grammar = (transition = (iterator = heap->data[0])->i[0])->grammar;
				
				struct gegexset* subgegexset = new_gegexset();
				
				struct stringset* tags = new_stringset();
				
				while (heap->n && strings_are_equal((transition = (iterator = heap->data[0])->i[0])->grammar, min_grammar))
				{
					heap_pop(heap);
					
					add_lambda_states(subgegexset, transition->to);
					
					stringset_update(tags, transition->tags);
					
					if (++iterator->i < iterator->n)
						heap_push(heap, iterator);
					else
						free(iterator);
				}
				
				struct avl_node_t* node = avl_search(mappings, &subgegexset);
				
				if (node)
				{
					struct mapping* old = node->item;
					
					gegex_add_grammar_transition(state, min_grammar, tags, old->combined_state);
					
					free_gegexset(subgegexset);
				}
				else
				{
					struct gegex* substate = new_gegex();
					
					struct mapping* new = new_mapping(subgegexset, substate);
					
					gegex_add_grammar_transition(state, min_grammar, tags, substate);
					
					quack_append(todo, new);
					
					avl_insert(mappings, new);
				}
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






















