
#include <assert.h>

#include <debug.h>

#include <avl/alloc_tree.h>
#include <avl/free_tree.h>

/*#include <avl/insert.h>*/

/*#include <memory/smalloc.h>*/
/*#include <memory/srealloc.h>*/

#include <heap/struct.h>
#include <heap/new.h>
#include <heap/push.h>
#include <heap/pop.h>
#include <heap/free.h>
#include <heap/is_nonempty.h>

#include <set/regex/new.h>
#include <set/regex/add.h>
#include <set/regex/foreach.h>
#include <set/regex/compare.h>
#include <set/regex/free.h>
#include <set/regex/len.h>
#include <set/regex/clear.h>
/*#include <set/regex/clone.h>*/

#include <named/regexset/compare.h>
#include <named/regexset/free.h>

#include <quack/len.h>

#include <macros/len.h>

#ifdef VERBOSE
/*#include <stdio.h>*/
/*#include <unistd.h>*/
/*#include <stdlib.h>*/
/*#include <signal.h>*/
/*#include <string.h>*/
/*#include <defines/argv0.h>*/
#include <cmdln/verbose.h>
#include <misc/default_sighandler.h>
#include <quack/struct.h>
#endif

#ifdef DEBUGGING
#include <quack/struct.h>
#endif

#include "../state/struct.h"
#include "../state/new.h"
#include "../state/transition/struct.h"
#include "../state/add_transition.h"
/*#include "../state/transition/struct.h"*/
#include "../state/foreach_transition.h"
#include "../state/foreach_lambda_transition.h"
/*#include "../state/set_accepting.h"*/
/*#include "../state/get_accepting.h"*/

#ifdef DOTOUT
#include "../dotout.h"
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
	
	this->stateset = stateset;
	
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
		regex_foreach_lambda_transition(ele, ({
			void runme(struct regex* state)
			{
				add_lambda_states(set, state);
			}
			runme;
		}));
	}
	
	EXIT;
}

struct regex* regex_nfa_to_dfa(
	struct regex* original_start
) {
	ENTER;
	
	struct quack* todo = new_quack();
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + todo->n;
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[k" "%s: regex_nfa_to_dfa: %u of %u (%.2f)\r", argv0,
				completed, total,
				(double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	if (verbose)
	{
		signal(SIGALRM, handler);
	}
	#endif
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	
	struct regex* new_start = new_regex();
	
	{
		struct regexset* start_set = new_regexset();
		
		add_lambda_states(start_set, original_start);
		
		struct mapping* mapping = new_mapping(start_set, new_start);
		
		quack_append(todo, mapping);
		
		avl_insert(mappings, mapping);
	}
	
	#ifdef DOTOUT
	regex_dotout(new_start, __PRETTY_FUNCTION__);
	#endif
	
	while (quack_len(todo))
	{
		dpv(todo->n);
		
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct mapping* mapping = pop_quack(todo);
		
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
			struct avl_node_t* node;
			
			struct regex* default_to;
			
			unsigned last_used;
		};
		
		struct iterator* new_iterator(struct regex* state)
		{
			ENTER;
			
			struct iterator* this = malloc(sizeof(*this));
			
			this->node = state->transitions->head;
			
			this->default_to = state->default_transition_to;
			
			this->last_used = -1;
			
			EXIT;
			return this;
		}
		
		int compare_iterators(const void* a, const void* b)
		{
			const struct iterator* A = a, *B = b;
			
			assert(A->node);
			assert(B->node);
			
			unsigned char value_a = ((struct regex_transition*) A->node->item)->value;
			unsigned char value_b = ((struct regex_transition*) B->node->item)->value;
			
			if (value_a > value_b)
				return +1;
			else if (value_a < value_b)
				return -1;
			else
				return 0;
		}

		struct heap* heap = new_heap(compare_iterators);
		
		// create default iterator list:
		struct {
			struct iterator** data;
			size_t n, cap;
		} defaults = {
			.data = NULL,
			.n = 0, .cap = 0,
		};
		
		struct regexset* EOF_subregexset = new_regexset();
			
		// create iterators for each state:
		regexset_foreach(stateset, ({
			void runme(struct regex* ele)
			{
				struct iterator* iter = new_iterator(ele);
				
				bool needed = false;
				
				if (iter->node)
				{
					heap_push(heap, iter);
					needed = true;
				}
				
				if (iter->default_to)
				{
					if (defaults.n + 1 > defaults.cap)
					{
						defaults.cap = defaults.cap << 1 ?: 1;
						
						dpv(defaults.cap);
						
						defaults.data = srealloc(defaults.data, sizeof(*defaults.data) * defaults.cap);
					}
					
					defaults.data[defaults.n++] = iter;
					needed = true;
				}
				
				if (ele->EOF_transition_to)
				{
					regexset_add(EOF_subregexset, ele->EOF_transition_to);
				}
				
				if (!needed)
				{
					free(iter);
				}
			}
			runme;
		}));
		
		unsigned round = 0;
		
		while (is_heap_nonempty(heap))
		{
			struct regexset* subregexset = new_regexset();
			
			struct iterator* iterator = heap->data[0];
			
			struct regex_transition* transition = iterator->node->item;
			
			unsigned min_value = transition->value;
			
			dpv(min_value);
			
			regexset_clear(subregexset);
			
			while (heap->n && (transition = (iterator = heap->data[0])->node->item)->value == min_value)
			{
				heap_pop(heap);
				
				add_lambda_states(subregexset, transition->to);
				
				iterator->node = iterator->node->next;
				
				iterator->last_used = round;
				
				if (iterator->node)
				{
					heap_push(heap, iterator);
				}
				else if (!iterator->default_to)
				{
					free(iterator);
				}
			}
			
			// for each iterator with defaults:
			for (size_t i = 0, n = defaults.n; i < n; i++)
				if (defaults.data[i]->last_used != round)
					add_lambda_states(subregexset, defaults.data[i]->default_to);
			
			struct avl_node_t* node = avl_search(mappings, &subregexset);
			
			if (node)
			{
				struct mapping* old = node->item;
				
				regex_add_transition(state, min_value, old->combined_state);
				
				free_regexset(subregexset);
			}
			else
			{
				struct regex* substate = new_regex();
				
				struct mapping* new = new_mapping(subregexset, substate);
				
				regex_add_transition(state, min_value, substate);
				
				quack_append(todo, new);
				avl_insert(mappings, new);
			}
			
			round++;
		}
		
		if (defaults.n)
		{
			TODO;
			#if 0
			// create regexset of all defaults
			#ifdef WITH_ARENAS
			struct regexset* subregexset = new_regexset(arena);
			#else
			struct regexset* subregexset = new_regexset();
			#endif
			
			for (size_t i = 0, n = defaults.n; i < n; i++)
				regex_add_lamda_states(subregexset, defaults.data[i]->default_to);
			
			// node.default = call myself
			struct regex* substate = regex_nfa_to_dfa_helper(
				#ifdef WITH_ARENAS
				/* arena: */ arena,
				#endif
				/* states: */ subregexset,
				/* mappings: */ mappings);
			
			regex_set_default_transition(state, substate);
			
			free_regexset(subregexset);
			#endif
		}
		
		// EOF transitions?
		if (regexset_len(EOF_subregexset))
		{
			TODO;
			#if 0
			struct regex* substate = regex_nfa_to_dfa_helper(
				#ifdef WITH_ARENAS
				/* arena: */ arena,
				#endif
				/* states: */ subregexset,
				/* mappings: */ mappings);
			
			regex_set_EOF_transition(state, substate);
			#endif
		}
		
		#ifdef DOTOUT
		regex_dotout(new_start, __PRETTY_FUNCTION__);
		#endif
		
		for (size_t i = 0, n = defaults.n; i < n; i++)
		{
			free(defaults.data[i]);
		}
		
		free_regexset(EOF_subregexset);
		
		free(defaults.data);
		
		free_heap(heap);
	}
	
	#ifdef VERBOSE
	if (verbose)
		signal(SIGALRM, default_sighandler);
	#endif
	
	avl_free_tree(mappings);
	
	free_quack(todo);
	
	EXIT;
	return new_start;
}













