
#if 0
#include <avl/search.h>

#include <debug.h>

#include <avl/safe_insert.h>

#include "../cache/struct.h"
#include "../cache/new.h"

#include <lex/state/struct.h>

#include "struct.h"
#include "find.h"

static bool lex_state_are_equal(
	struct avl_tree_t* cache,
	struct lex_state* a,
	struct lex_state* b)
{
	bool are_equal = true;
	ENTER;
	
	dpv(a);
	dpv(b);
	
	struct avl_node_t* node = avl_search(cache, &(struct lex_state_cache){a, b});
	
	struct lex_state_cache* ele;
	
	if (node)
	{
		TODO;
	}
	else
	{
		safe_avl_insert(cache, ele = new_lex_state_cache(a, b));
		
		if (a == b)
		{
			ddprintf("exactly same\n");
			are_equal = true;
		}
		else if (!!a->accepting > !!b->accepting)
		{
			ddprintf("A is accepting and B is not\n");
			are_equal = false;
		}
		else if (!!a->accepting < !!b->accepting)
		{
			ddprintf("B is accepting and A is not\n");
			are_equal = false;
		}
		else if (a->accepting && b->accepting)
		{
			TODO;
		}
		else
		{
			size_t a_i = 0, a_n = a->transitions.n;
			size_t b_i = 0, b_n = b->transitions.n;
			
			while (are_equal && a_i < a_n && b_i < b_n)
			{
				dpv(a_i);
				dpv(b_i);
				
				TODO;
				#if 0
				const struct transition* ele_a = a->transitions.data[a_i];
				const struct transition* ele_b = b->transitions.data[b_i];
				
				dpv(ele_a->value);
				dpv(ele_b->value);
				
				if (ele_a->value < ele_b->value)
				{
					if (b->default_transition_to)
					{
						are_equal = lex_state_are_equal(
							cache, ele_a->to, b->default_transition_to);
					}
					else
					{
						are_equal = false;
					}
					
					a_i++;
				}
				else if (ele_a->value > ele_b->value)
				{
					if (a->default_transition_to)
					{
						are_equal = lex_state_are_equal(
							cache, ele_b->to, a->default_transition_to);
					}
					else
					{
						are_equal = false;
					}
					
					b_i++;
				}
				else
				{
					are_equal = lex_state_are_equal(cache, ele_a->to, ele_b->to);
					a_i++, b_i++;
				}
				#endif
			}
			
			while (are_equal && a_i < a_n && b->default_transition_to)
			{
				TODO;
				#if 0
				const struct transition* ele_a = a->transitions.data[a_i++];
				
				are_equal = lex_state_are_equal(cache, ele_a->to, b->default_transition_to);
				#endif
			}
			
			while (are_equal && b_i < b_n && a->default_transition_to)
			{
				TODO;
			}
			
			if (are_equal)
			{
				if (a_i < a_n || b_i < b_n)
				{
					are_equal = false;
				}
				else if (a->default_transition_to && !b->default_transition_to)
				{
					TODO;
				}
				else if (!a->default_transition_to && b->default_transition_to)
				{
					TODO;
				}
				else if (a->default_transition_to && b->default_transition_to)
				{
					are_equal = lex_state_are_equal(cache,
						a->default_transition_to, b->default_transition_to);
				}
			}
		}
		
		ele->are_equal = are_equal;
	}
	
	EXIT;
	return are_equal;
}

struct lex_state* lex_state_ll_find(
	struct lex_state_ll* this,
	struct lex_state* state)
{
	struct lex_state* found = NULL;
	ENTER;
	
	for (struct lex_state_link* link = this->head; !found && link; link = link->next)
	{
		dpv(link);
		
		if (lex_state_are_equal(this->cache, link->element, state))
		{
			TODO;
		}
	}
	
	dpv(found);
	
	EXIT;
	return found;
}
















#endif
