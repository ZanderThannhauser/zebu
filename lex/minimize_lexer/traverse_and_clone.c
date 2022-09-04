
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

/*#include <avl/alloc_tree.h>*/
/*#include <avl/search.h>*/
/*#include <avl/insert.h>*/
/*#include <avl/free_tree.h>*/

#include <set/lexstate/struct.h>

#include <set/yaccstate/new.h>
#include <set/yaccstate/add.h>
#include <set/yaccstate/free.h>

#include <yacc/state/struct.h>

#ifdef VERBOSE
#include <misc/default_sighandler.h>
#endif

#include "../state/struct.h"
#include "../state/new.h"
#include "../state/add_transition.h"
#include "../state/set_default_transition.h"
#include "../state/set_EOF_transition.h"

#include "same_as_node/struct.h"

#include "traverse_and_clone.h"

static struct mapping {
	struct lex_state* old;
	struct lex_state* new;
}* new_mapping(struct lex_state* old, struct lex_state* new)
{
	struct mapping* this = smalloc(sizeof(*this));
	this->old = old, this->new = new;
	return this;
}

static int compare_mappings(const void* a, const void* b)
{
	const struct mapping* A = a, *B = b;
	
	if (A->old > B->old)
		return +1;
	else if (A->old < B->old)
		return -1;
	else
		return  0;
}

static struct lex_state* find(struct avl_tree_t* connections, struct lex_state* a)
{
	struct avl_node_t* node = avl_search(connections, &a);
	
	assert(node);
	
	struct lex_same_as_node* sa = node->item;
	
	assert(sa->set->len);
	
	return sa->set->tree->head->item;
}

void lex_minimize_traverse_and_clone(
	struct avl_tree_t* connections,
	struct yacc_state* start)
{
	ENTER;
	
	struct quack* yacc_todo = new_quack();
	
	struct quack* lex_todo = new_quack();
	
	struct yaccstateset* queued = new_yaccstateset();
	
	yaccstateset_add(queued, start);
	
	quack_append(yacc_todo, start);
	
	#ifdef VERBOSE
	unsigned yacc_completed = 0;
	
	unsigned lex_completed = 0;
	
	void handler(int _)
	{
		char buffer[1000] = {};
		
		unsigned yacc_total = yacc_completed + quack_len(yacc_todo);
		unsigned  lex_total =  lex_completed + quack_len( lex_todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "zebu: minimize lexer (clone): %u of %u (%.2f%%) | %u of %u (%.2f%%)\r",
				yacc_completed, yacc_total, (double) yacc_completed * 100 / yacc_total,
				 lex_completed,  lex_total, (double)  lex_completed * 100 /  lex_total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler);
	#endif
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free);
	
	struct lex_state* clone(struct lex_state* cloneme)
	{
		struct lex_state* retval = new_lex_state();
		
		struct mapping* mapping = new_mapping(cloneme, retval);
		
		avl_insert(mappings, mapping);
		
		quack_append(lex_todo, mapping);
		
		while (quack_len(lex_todo))
		{
			#ifdef VERBOSE
			lex_completed++;
			#endif
			
			struct mapping* mapping = quack_pop(lex_todo);
			
			struct lex_state* const old = mapping->old;
			struct lex_state* const new = mapping->new;
			
			new->accepts = old->accepts;
			
			if (old->default_transition.to)
			{
				struct lex_state* subold = find(connections, old->default_transition.to);
				
				struct avl_node_t* node = avl_search(mappings, &subold);
				
				if (node)
				{
					struct mapping* submapping = node->item;
					
					lex_state_set_default_transition(new, old->default_transition.exceptions, submapping->new);
				}
				else
				{
					struct lex_state* substate = new_lex_state();
					
					struct mapping* submapping = new_mapping(subold, substate);
					
					lex_state_set_default_transition(new, old->default_transition.exceptions, substate);
					
					avl_insert(mappings, submapping);
					
					quack_append(lex_todo, submapping);
				}
			}
			
			// for each transition:
			for (unsigned i = 0, n = old->transitions.n; i < n; i++)
			{
				struct lex_transition* const ele = old->transitions.data[i];
				
				struct lex_state* subold = find(connections, ele->to);
				
				struct avl_node_t* node = avl_search(mappings, &subold);
				
				if (node)
				{
					struct mapping* submapping = node->item;
					
					if (new->default_transition.to != submapping->new)
					{
						lex_state_add_transition(new, ele->value, submapping->new);
					}
				}
				else
				{
					struct lex_state* substate = new_lex_state();
					
					struct mapping* submapping = new_mapping(subold, substate);
					
					lex_state_add_transition(new, ele->value, substate);
					
					avl_insert(mappings, submapping);
					
					quack_append(lex_todo, submapping);
				}
			}
			
			// EOF transitions?
			if (old->EOF_transition_to)
			{
				struct lex_state* subold = find(connections, old->EOF_transition_to);
				
				struct avl_node_t* node = avl_search(mappings, &subold);
				
				if (node)
				{
					struct mapping* submapping = node->item;
					
					lex_state_set_EOF_transition(new, submapping->new);
				}
				else
				{
					struct lex_state* substate = new_lex_state();
					
					struct mapping* submapping = new_mapping(subold, substate);
					
					lex_state_set_EOF_transition(new, substate);
					
					avl_insert(mappings, submapping);
					
					quack_append(lex_todo, submapping);
				}
			}
		}
		
		return retval;
	}
	
	while (quack_len(yacc_todo))
	{
		#ifdef VERBOSE
		yacc_completed++;
		#endif
		
		struct yacc_state* state = quack_pop(yacc_todo);
		
		struct lex_state* cloneme = find(connections, state->tokenizer_start);
		
		struct avl_node_t* node = avl_search(mappings, &cloneme);
		
		if (node)
			state->tokenizer_start = ((struct mapping*) node->item)->new;
		else
			state->tokenizer_start = clone(cloneme);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct yacc_state* const to = state->transitions.data[i]->to;
			
			if (yaccstateset_add(queued, to))
				quack_append(yacc_todo, to);
		}
		
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct yacc_state* const to = state->grammar_transitions.data[i]->to;
			
			if (yaccstateset_add(queued, to))
				quack_append(yacc_todo, to);
		}
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	free_yaccstateset(queued);
	
	avl_free_tree(mappings);
	
	free_quack(yacc_todo);
	
	free_quack(lex_todo);
	
	EXIT;
}











































