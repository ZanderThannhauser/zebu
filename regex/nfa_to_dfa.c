
#include <assert.h>

#include <debug.h>

/*#include <avl/alloc_tree.h>*/
/*#include <avl/free_tree.h>*/

#include <heap/struct.h>
#include <heap/len.h>
#include <heap/new.h>
#include <heap/push.h>
#include <heap/pop.h>
#include <heap/free.h>

#include <set/regex/new.h>
#include <set/regex/add.h>
#include <set/regex/foreach.h>
#include <set/regex/compare.h>
#include <set/regex/free.h>
#include <set/regex/len.h>
#include <set/regex/inc.h>

#include <set/unsignedchar/new.h>
#include <set/unsignedchar/add.h>
#include <set/unsignedchar/contains.h>
#include <set/unsignedchar/foreach.h>
#include <set/unsignedchar/free.h>

/*#include <named/regexset/compare.h>*/
/*#include <named/regexset/free.h>*/

#ifdef VERBOSE
/*#include <stdio.h>*/
/*#include <unistd.h>*/
/*#include <stdlib.h>*/
/*#include <signal.h>*/
/*#include <string.h>*/
#include <misc/default_sighandler.h>
#endif

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"
#include "state/set_default_transition.h"
#include "state/set_EOF_transition.h"

#ifdef DOTOUT
#include "dotout.h"
#endif

#include "nfa_to_dfa.h"

struct mapping
{
	struct regexset* stateset; // must be the first
	
	struct regex* combined_state;
};

static struct mapping* new_mapping(
	struct regexset* stateset,
	struct regex* state)
{
	ENTER;
	
	struct mapping* this = smalloc(sizeof(*this));
	
	this->stateset = inc_regexset(stateset);
	
	this->combined_state = state;
	
	EXIT;
	return this;
}

static int compare_mappings(const void* a, const void* b)
{
	const struct mapping *A = a, *B = b;
	return compare_regexsets(A->stateset, B->stateset);
}

static void free_mapping(void* a)
{
	struct mapping* this = a;
	ENTER;
	
	free_regexset(this->stateset);
	
	free(this);
	
	EXIT;
}


static void add_lambda_states(struct regexset* set, struct regex* ele)
{
	ENTER;
	
	if (regexset_add(set, ele))
	{
		for (unsigned i = 0, n = ele->lambda_transitions.n; i < n; i++)
		{
			add_lambda_states(set, ele->lambda_transitions.data[i]);
		}
	}
	
	EXIT;
}

struct regex* regex_nfa_to_dfa(struct regex* original_start)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + quack_len(todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[k" "zebu: regex nfa-to-dfa: %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler);
	#endif
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	
	struct regex* new_start = new_regex();
	
	{
		struct regexset* start_set = new_regexset();
		
		add_lambda_states(start_set, original_start);
		
		struct mapping* mapping = new_mapping(start_set, new_start);
		
		quack_append(todo, mapping);
		
		avl_insert(mappings, mapping);
		
		free_regexset(start_set);
	}
	
	#ifdef DOTOUT
	regex_dotout(new_start, __PRETTY_FUNCTION__);
	#endif
	
	while (quack_len(todo))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct mapping* mapping = quack_pop(todo);
		
		struct regexset* const stateset = mapping->stateset;
		
		struct regex* const state = mapping->combined_state;
		
		// set this as accepting if any states in list are accepting:
		{
			bool is_accepting = false;
			
			regexset_foreach(stateset, ({
				void runme(struct regex* ele) {
					if (ele->is_accepting) {
						is_accepting = true;
					}
				}
				runme;
			}));
			
			state->is_accepting = is_accepting;
			
			dpvb(is_accepting);
		}
		
		struct iterator
		{
			struct regex_transition **i, **n;
		};
		
		struct iterator* new_iterator(struct regex* state)
		{
			struct iterator* this = smalloc(sizeof(*this));
			
			this->i = state->transitions.data;
			
			this->n = state->transitions.data + state->transitions.n;
			
			return this;
		}
		
		int compare_iterators(const void* a, const void* b)
		{
			const struct iterator* A = a, *B = b;
			
			unsigned char value_a = A->i[0]->value;
			unsigned char value_b = B->i[0]->value;
			
			if (value_a > value_b)
				return +1;
			else if (value_a < value_b)
				return -1;
			else
				return 0;
		}
		
		int compare_chars(const void* a, const void* b)
		{
			const unsigned char *A = a, *B = b;
			if (*A > *B)
				return +1;
			else if (*A < *B)
				return -1;
			else
				return +0;
		}
		
		struct heap* heap = new_heap(compare_iterators);
		
		struct heap* exceptions = new_heap(compare_chars);
		
		struct unsignedcharset* alphabet = new_unsignedcharset();
		
		// create default iterator list:
		struct {
			struct {
				struct unsignedcharset* exceptions;
				struct regex* to;
			}* data;
			size_t n, cap;
		} defaults = {
			.data = NULL,
			.n = 0, .cap = 0,
		};
		
		struct regexset* default_subregexset = new_regexset();
		struct regexset* EOF_subregexset = new_regexset();
		
		// create iterators for each state:
		regexset_foreach(stateset, ({
			void runme(struct regex* ele)
			{
				if (ele->transitions.n)
				{
					struct iterator* iter = new_iterator(ele);
					heap_push(heap, iter);
				}
				
				if (ele->default_transition.to)
				{
					if (defaults.n + 1 > defaults.cap)
					{
						defaults.cap = defaults.cap << 1 ?: 1;
						
						dpv(defaults.cap);
						
						defaults.data = srealloc(defaults.data, sizeof(*defaults.data) * defaults.cap);
					}
					
					defaults.data[defaults.n].to = ele->default_transition.to;
					
					defaults.data[defaults.n].exceptions = ele->default_transition.exceptions;
					
					defaults.n++;
					
					add_lambda_states(default_subregexset, ele->default_transition.to);
					
					unsignedcharset_foreach(ele->default_transition.exceptions, ({
						void runme(unsigned char value)
						{
							dpv(value);
							
							unsigned char* dup = smalloc(sizeof(*dup));
							
							*dup = value;
							
							heap_push(exceptions, dup);
						}
						runme;
					}));
				}
				
				if (ele->EOF_transition_to)
				{
					regexset_add(EOF_subregexset, ele->EOF_transition_to);
				}
			}
			runme;
		}));
		
		while (heap_len(heap) || heap_len(exceptions))
		{
			struct iterator* iterator;
			
			struct regex_transition* transition;
			
			unsigned char *except;
			
			unsigned min_value = -1;
			
			if (heap->n)
			{
				unsigned my_min = (iterator = heap->data[0])->i[0]->value;
				
				dpv(my_min);
				
				if (my_min < min_value)
					min_value = my_min;
			}
			
			if (exceptions->n)
			{
				unsigned my_min = *(except = exceptions->data[0]);
				
				dpv(my_min);
				
				if (my_min < min_value)
					min_value = my_min;
			}
			
			dpv(min_value);
			
			unsignedcharset_add(alphabet, min_value);
			
			struct regexset* subregexset = new_regexset();
			
			while (heap->n && (transition = (iterator = heap->data[0])->i[0])->value == min_value)
			{
				heap_pop(heap);
				
				add_lambda_states(subregexset, transition->to);
				
				if (++iterator->i < iterator->n)
					heap_push(heap, iterator);
				else
					free(iterator);
			}
			
			while (exceptions->n && *(except = exceptions->data[0]) == min_value)
			{
				heap_pop(exceptions);
				
				free(except);
			}
			
			// for each iterator with defaults:
			for (size_t i = 0, n = defaults.n; i < n; i++)
				if (!unsignedcharset_contains(defaults.data[i].exceptions, min_value))
					add_lambda_states(subregexset, defaults.data[i].to);
			
			if (regexset_len(subregexset))
			{
				struct avl_node_t* node = avl_search(mappings, &subregexset);
				
				if (node)
				{
					struct mapping* old = node->item;
					
					regex_add_transition(state, min_value, old->combined_state);
				}
				else
				{
					struct regex* substate = new_regex();
					
					struct mapping* new = new_mapping(subregexset, substate);
					
					regex_add_transition(state, min_value, substate);
					
					quack_append(todo, new);
					
					avl_insert(mappings, new);
				}
			}
			
			free_regexset(subregexset);
		}
		
		if (defaults.n)
		{
			struct avl_node_t* node = avl_search(mappings, &default_subregexset);
			
			if (node)
			{
				struct mapping* old = node->item;
				
				regex_set_default_transition(state, alphabet, old->combined_state);
			}
			else
			{
				struct regex* substate = new_regex();
				
				struct mapping* new = new_mapping(default_subregexset, substate);
				
				regex_set_default_transition(state, alphabet, substate);
				
				quack_append(todo, new);
				
				avl_insert(mappings, new);
			}
		}
		
		// EOF transitions?
		if (regexset_len(EOF_subregexset))
		{
			struct avl_node_t* node = avl_search(mappings, &EOF_subregexset);
			
			if (node)
			{
				struct mapping* old = node->item;
				
				regex_set_EOF_transition(state, old->combined_state);
			}
			else
			{
				struct regex* substate = new_regex();
				
				struct mapping* new = new_mapping(EOF_subregexset, substate);
				
				regex_set_EOF_transition(state, substate);
				
				quack_append(todo, new);
				
				avl_insert(mappings, new);
			}
		}
		
		#ifdef DOTOUT
		regex_dotout(new_start, __PRETTY_FUNCTION__);
		#endif
		
		free(defaults.data);
		
		free_regexset(default_subregexset);
		
		free_regexset(EOF_subregexset);
			
		free_unsignedcharset(alphabet);
		
		free_heap(heap);
		
		free_heap(exceptions);
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	avl_free_tree(mappings);
	
	free_quack(todo);
	
	EXIT;
	return new_start;
}













