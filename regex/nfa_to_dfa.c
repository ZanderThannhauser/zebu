
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
			"\e[K" "zebu: regex nfa-to-dfa: %u of %u (%.2f%%)\r",
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
		
		struct mapping* const mapping = quack_pop(todo);
		
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
		
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regexset* subregexset = new_regexset();
			
			regexset_foreach(stateset, ({
				void runme(struct regex* ele)
				{
					struct regex* const to = ele->transitions[i];
					if (to) add_lambda_states(subregexset, to);
				}
				runme;
			}));
			
			if (regexset_len(subregexset))
			{
				struct avl_node_t* node = avl_search(mappings, &subregexset);
				
				if (node)
				{
					struct mapping* old = node->item;
					
					state->transitions[i] = old->combined_state;
				}
				else
				{
					struct regex* substate = new_regex();
					
					struct mapping* new = new_mapping(subregexset, substate);
					
					state->transitions[i] = substate;
					
					quack_append(todo, new);
					
					avl_insert(mappings, new);
				}
			}
			
			free_regexset(subregexset);
		}
		
		// EOF transitions?
		{
			struct regexset* subregexset = new_regexset();
			
			regexset_foreach(stateset, ({
				void runme(struct regex* ele)
				{
					struct regex* const to = ele->EOF_transition_to;
					if (to) add_lambda_states(subregexset, to);
				}
				runme;
			}));
			
			if (regexset_len(subregexset))
			{
				struct avl_node_t* node = avl_search(mappings, &subregexset);
				
				if (node)
				{
					struct mapping* old = node->item;
					
					state->EOF_transition_to = old->combined_state;
				}
				else
				{
					struct regex* substate = new_regex();
					
					struct mapping* new = new_mapping(subregexset, substate);
					
					state->EOF_transition_to = substate;
					
					quack_append(todo, new);
					
					avl_insert(mappings, new);
				}
			}
			
			free_regexset(subregexset);
		}
		
		#ifdef DOTOUT
		regex_dotout(new_start, __PRETTY_FUNCTION__);
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













