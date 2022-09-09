
#include <stdbool.h>
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/search.h>
#include <avl/free_tree.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/len.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/regex/new.h>
#include <set/regex/compare.h>
#include <set/regex/add.h>
#include <set/regex/inc.h>
#include <set/regex/free.h>
#include <set/regex/foreach.h>
#include <set/regex/len.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/inc.h>
#include <set/unsigned/len.h>
#include <set/unsigned/clear.h>
/*#include <set/unsigned/free.h>*/

#include <set/unsignedset/new.h>
#include <set/unsignedset/add.h>

#include <lex/state/struct.h>
#include <lex/state/new.h>
/*#include <lex/state/dotout.h>*/

#include <regex/state/struct.h>
/*#include <regex/dotout.h>*/

#ifdef DOTOUT
#include <regex/dotout.h>
#include <lex/state/dotout.h>
#endif

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
		
		// normal transitions:
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regexset* subregexset = new_regexset();
			
			regexset_foreach(stateset, ({
				void runme(struct regex* substate) {
					struct regex* to = substate->transitions[i];
					if (to) regexset_add(subregexset, to);
				}
				runme;
			}));
			
			if (regexset_len(subregexset))
			{
				struct avl_node_t* node = avl_search(mappings, &subregexset);
				
				if (node)
				{
					struct mapping* old = node->item;
					
					state->transitions[i] = old->state;
				}
				else
				{
					struct lex_state* substate = new_lex_state();
					
					struct mapping* new = new_mapping(subregexset, substate);
					
					state->transitions[i] = substate;
					
					quack_append(todo, new);
					
					avl_insert(mappings, new);
				}
			}
			
			free_regexset(subregexset);
		}
		
		// EOF transitions:
		{
			struct regexset* subregexset = new_regexset();
			
			regexset_foreach(stateset, ({
				void runme(struct regex* substate) {
					struct regex* to = substate->EOF_transition_to;
					if (to) regexset_add(subregexset, to);
				}
				runme;
			}));
			
			if (regexset_len(subregexset))
			{
				struct avl_node_t* node = avl_search(mappings, &subregexset);
				
				if (node)
				{
					struct mapping* old = node->item;
					
					state->EOF_transition_to = old->state;
				}
				else
				{
					struct lex_state* substate = new_lex_state();
					
					struct mapping* new = new_mapping(subregexset, substate);
					
					state->EOF_transition_to = substate;
					
					quack_append(todo, new);
					
					avl_insert(mappings, new);
				}
			}
			
			free_regexset(subregexset);
		}
		
		#ifdef DOTOUT
		lex_state_dotout(start);
		#endif
	}
	
	avl_free_tree(mappings);
	
	free_quack(todo);
	
	*outgoing = start;
	
	EXIT;
	return all_accepts;
}







