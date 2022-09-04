
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

/*#include <avl/search.h>*/
/*#include <avl/free_tree.h>*/
/*#include <avl/alloc_tree.h>*/
/*#include <avl/insert.h>*/

#include <set/unsignedchar/contains.h>

#ifdef VERBOSE
#include <misc/default_sighandler.h>
#endif

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"

#include "dotout.h"

#include "intersect_dfas.h"

struct mapping
{
	struct regex* a, *b;
	struct regex* new;
};

static struct mapping* new_mapping(
	struct regex* a, struct regex* b,
	struct regex* new)
{
	ENTER;
	
	struct mapping* this = smalloc(sizeof(*this));
	
	this->a = a;
	this->b = b;
	this->new = new;
	
	EXIT;
	return this;
}

static int compare(const void* a, const void* b)
{
	const struct mapping *A = a, *B = b;
	
	if (A->a > B->a)
		return +1;
	if (A->a < B->a)
		return +1;
	if (A->b > B->b)
		return +1;
	if (A->b < B->b)
		return +1;
	
	return 0;
}

struct regex* regex_intersect_dfas(struct regex* A_start, struct regex* B_start)
{
	ENTER;
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare, free);
	
	struct quack* todo = new_quack();
	
	struct regex* new_start = new_regex();
	
	{
		struct mapping* mapping = new_mapping(A_start, B_start, new_start);
		
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
			"\e[k" "zebu: regex intersect: %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler);
	#endif
	
	while (quack_len(todo))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct mapping* mapping = quack_pop(todo);
		
		struct regex* const A = mapping->a;
		struct regex* const B = mapping->b;
		struct regex* const state = mapping->new;
		
		state->is_accepting = A->is_accepting && B->is_accepting;
		
		dpvb(state->is_accepting);
		
		struct {size_t i, n;} a = {0, A->transitions.n}, b = {0, B->transitions.n};
		
		dpv(a.n);
		dpv(b.n);
		
		while (a.i < a.n && b.i < b.n)
		{
			struct regex_transition* const A_trans = A->transitions.data[a.i];
			struct regex_transition* const B_trans = B->transitions.data[b.i];
			
			if (A_trans->value < B_trans->value)
			{
				TODO;
				#if 0
				dpv(A_trans->value);
				
				if (B->default_transition_to)
				{
					#ifdef WITH_ARENAS
					struct regex* substate = helper(arena, mappings, A_trans->to, B->default_transition_to);
					#else
					struct regex* substate = helper(mappings, A_trans->to, B->default_transition_to);
					#endif
					
					regex_add_transition(state, A_trans->value, substate);
				}
				
				a.i++;
				#endif
			}
			else if (A_trans->value > B_trans->value)
			{
				dpv(B_trans->value);
				
				if (A->default_transition.to)
				{
					TODO;
				}
				
				b.i++;
			}
			else
			{
				TODO;
				#if 0
				dpv(A_trans->value);
				
				#ifdef WITH_ARENAS
				struct regex* substate = helper(arena, mappings, A_trans->to, B_trans->to);
				#else
				struct regex* substate = helper(mappings, A_trans->to, B_trans->to);
				#endif
				
				regex_add_transition(state, A_trans->value, substate);
				
				a.i++, b.i++;
				#endif
			}
		}
		
		while (a.i < a.n && B->default_transition.to)
		{
			struct regex_transition* const A_trans = A->transitions.data[a.i++];
			
			if (!unsignedcharset_contains(B->default_transition.exceptions, A_trans->value))
			{
				struct avl_node_t* node = avl_search(mappings, &(struct mapping) {A_trans->to, B->default_transition.to});
				
				if (node)
				{
					struct mapping* submapping = node->item;
					
					regex_add_transition(state, A_trans->value, submapping->new);
				}
				else
				{
					struct regex* substate = new_regex();
					
					struct mapping* submapping = new_mapping(A_trans->to, B->default_transition.to, substate);
					
					regex_add_transition(state, A_trans->value, substate);
					
					avl_insert(mappings, submapping);
					
					quack_append(todo, submapping);
				}
			}
		}
		
		while (A->default_transition.to && b.i < b.n)
		{
			// const struct transition* const B_trans = B->transitions.data[b.i++];
			TODO;
		}
		
		if (A->default_transition.to && B->default_transition.to)
		{
			TODO;
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












