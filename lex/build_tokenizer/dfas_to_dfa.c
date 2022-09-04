
#include <debug.h>

#include <regex/state/struct.h>
#include <regex/dotout.h>

#include <set/regex/foreach.h>

#include <lex/state/struct.h>
#include <lex/state/new.h>
#include <lex/state/add_transition.h>
#include <lex/state/set_default_transition.h>
#include <lex/state/set_EOF_transition.h>
#include <lex/state/dotout.h>

#include <set/regex/new.h>
#include <set/regex/compare.h>
#include <set/regex/add.h>
#include <set/regex/inc.h>
#include <set/regex/free.h>
#include <set/regex/len.h>

#include <heap/struct.h>
#include <heap/len.h>
#include <heap/new.h>
#include <heap/push.h>
#include <heap/pop.h>
#include <heap/free.h>

#include <set/unsignedchar/new.h>
#include <set/unsignedchar/add.h>
#include <set/unsignedchar/contains.h>
#include <set/unsignedchar/foreach.h>
#include <set/unsignedchar/free.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/inc.h>
#include <set/unsigned/len.h>
#include <set/unsigned/clear.h>
#include <set/unsigned/free.h>

#include <set/unsignedset/new.h>
#include <set/unsignedset/add.h>

#include "dfas_to_dfa.h"

struct mapping
{
	struct regexset* regexset; // must be first
	struct lex_state* state;
};

static struct mapping* new_mapping(
	struct regexset* regexset,
	struct lex_state* state)
{
	ENTER;
	
	struct mapping* this = smalloc(sizeof(*this));
	
	this->regexset = inc_regexset(regexset);
	
	this->state = state;
	
	EXIT;
	return this;
}

static int compare_mappings(const void* a, const void* b)
{
	const struct mapping *A = a, *B = b;
	
	return compare_regexsets(A->regexset, B->regexset);
}

static void free_mapping(void* ptr)
{
	struct mapping* mapping = ptr;
	
	free_regexset(mapping->regexset);
	free(mapping);
}

struct unsignedsetset* dfas_to_dfa(
	struct lex_state** outgoing,
	struct regexset* starts)
{
	ENTER;
	
	#ifdef DOTOUT
	regex_dotout_set(starts, __PRETTY_FUNCTION__);
	#endif
	
	struct quack* todo = new_quack();
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	
	struct unsignedsetset* all_accepts = new_unsignedsetset();
	
	struct lex_state* start = new_lex_state();
	
	{
		struct mapping* new = new_mapping(starts, start);
		
		quack_append(todo, new);
		
		avl_insert(mappings, new);
	}
	
	#ifdef DOTOUT
	lex_state_dotout(start);
	#endif
	
	while (quack_len(todo))
	{
		struct mapping* const mapping = quack_pop(todo);
		
		struct regexset* const stateset = mapping->regexset;
		
		struct lex_state* const state = mapping->state;
		
		bool is_literal = false;
		
		struct unsignedset* accepts = new_unsignedset();
		
		regexset_foreach(stateset, ({
			void runme(struct regex* substate)
			{
				if (substate->is_accepting)
				{
					if (substate->is_literal > is_literal)
					{
						unsignedset_clear(accepts);
						unsignedset_add(accepts, substate->is_accepting);
						is_literal = substate->is_literal;
					}
					else if (substate->is_literal == is_literal)
					{
						unsignedset_add(accepts, substate->is_accepting);
					}
				}
			}
			runme;
		}));
		
		if (unsignedset_len(accepts))
		{
			unsignedsetset_add(all_accepts, accepts);
			
			state->accepts = inc_unsignedset(accepts);
		}
		
		struct iterator
		{
			struct regex_transition **i, **n;
		};
		
		struct iterator* new_iterator(struct regex* state)
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
					if (defaults.n == defaults.cap)
					{
						defaults.cap = defaults.cap << 1 ?: 1;
						
						dpv(defaults.cap);
						
						defaults.data = srealloc(defaults.data, sizeof(*defaults.data) * defaults.cap);
					}
					
					regexset_add(default_subregexset, ele->default_transition.to);
					
					defaults.data[defaults.n].to = ele->default_transition.to;
					
					defaults.data[defaults.n].exceptions = ele->default_transition.exceptions;
					
					defaults.n++;
					
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
		
		// normal transitions:
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
				
				regexset_add(subregexset, transition->to);
				
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
					regexset_add(subregexset, defaults.data[i].to);
			
			if (regexset_len(subregexset))
			{
				struct avl_node_t* node = avl_search(mappings, &subregexset);
				
				if (node)
				{
					struct mapping* old = node->item;
					
					lex_state_add_transition(state, min_value, old->state);
				}
				else
				{
					struct lex_state* substate = new_lex_state();
					
					struct mapping* new = new_mapping(subregexset, substate);
					
					lex_state_add_transition(state, min_value, substate);
					
					quack_append(todo, new);
					
					avl_insert(mappings, new);
				}
			}
			
			free_regexset(subregexset);
		}
		
		// default transitions:
		if (regexset_len(default_subregexset))
		{
			struct avl_node_t* node = avl_search(mappings, &default_subregexset);
			
			if (node)
			{
				struct mapping* old = node->item;
				
				lex_state_set_default_transition(state, alphabet, old->state);
			}
			else
			{
				struct lex_state* substate = new_lex_state();
				
				struct mapping* new = new_mapping(default_subregexset, substate);
				
				lex_state_set_default_transition(state, alphabet, substate);
				
				quack_append(todo, new);
				
				avl_insert(mappings, new);
			}
		}
		
		// EOF transitions:
		if (regexset_len(EOF_subregexset))
		{
			struct avl_node_t* node = avl_search(mappings, &EOF_subregexset);
			
			if (node)
			{
				struct mapping* old = node->item;
				
				lex_state_set_EOF_transition(state, old->state);
			}
			else
			{
				struct lex_state* substate = new_lex_state();
				
				struct mapping* new = new_mapping(EOF_subregexset, substate);
				
				lex_state_set_EOF_transition(state, substate);
				
				quack_append(todo, new);
				
				avl_insert(mappings, new);
			}
		}
		
		#ifdef DOTOUT
		lex_state_dotout(start);
		#endif
		
		free_regexset(EOF_subregexset);
		
		free_regexset(default_subregexset);
		
		free_unsignedcharset(alphabet);
		
		free_unsignedset(accepts);
		
		free(defaults.data);
	}
	
	avl_free_tree(mappings);
	
	free_quack(todo);
	
	*outgoing = start;
	
	EXIT;
	return all_accepts;
}







