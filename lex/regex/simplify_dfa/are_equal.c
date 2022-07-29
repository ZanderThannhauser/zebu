
#include <assert.h>

#include <avl/avl.h>
#include <avl/search.h>
#include <avl/safe_insert.h>

#include <debug.h>

#include "../state/struct.h"

#include "cache/struct.h"
#include "cache/new.h"

#include "are_equal.h"

bool regex_are_equal(
	struct avl_tree_t* cache,
	const struct regex* a,
	const struct regex* b)
{
	bool are_equal = true;
	ENTER;
	
	dpv(a);
	dpv(b);
	
	struct avl_node_t* node = avl_search(cache, &(struct regex_cache){a, b});
	
	struct regex_cache* ele;
	
	if (node)
	{
		ddprintf("retrieved from cache\n");
		
		ele = node->item;
		
		are_equal = ele->are_equal;
	}
	else
	{
		safe_avl_insert(cache, ele = new_regex_cache(a, b));
		
		if (a == b)
		{
			ddprintf("exactly same\n");
			are_equal = true;
		}
		else if (!!a->is_accepting > !!b->is_accepting)
		{
			ddprintf("A is accepting and B is not\n");
			are_equal = false;
		}
		else if (!!a->is_accepting < !!b->is_accepting)
		{
			ddprintf("B is accepting and A is not\n");
			are_equal = false;
		}
		else
		{
			size_t a_i = 0, a_n = a->transitions.n;
			size_t b_i = 0, b_n = b->transitions.n;
			
			while (are_equal && a_i < a_n && b_i < b_n)
			{
				dpv(a_i);
				dpv(b_i);
				
				const struct transition* ele_a = a->transitions.data[a_i];
				const struct transition* ele_b = b->transitions.data[b_i];
				
				dpv(ele_a->value);
				dpv(ele_b->value);
				
				if (ele_a->value < ele_b->value)
				{
					if (b->default_transition_to)
					{
						are_equal = regex_are_equal(
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
						are_equal = regex_are_equal(
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
					are_equal = regex_are_equal(cache, ele_a->to, ele_b->to);
					a_i++, b_i++;
				}
			}
			
			while (are_equal && a_i < a_n && b->default_transition_to)
			{
				const struct transition* ele_a = a->transitions.data[a_i++];
				
				are_equal = regex_are_equal(cache, ele_a->to, b->default_transition_to);
			}
			
			while (are_equal && a->default_transition_to && b_i < b_n)
			{
				const struct transition* ele_b = b->transitions.data[b_i++];
				
				are_equal = regex_are_equal(cache, a->default_transition_to, ele_b->to);
			}
			
			if (are_equal)
			{
				if (a_i < a_n || b_i < b_n)
				{
					are_equal = false;
				}
				else if (a->default_transition_to && !b->default_transition_to)
				{
					are_equal = false;
				}
				else if (!a->default_transition_to && b->default_transition_to)
				{
					are_equal = false;
				}
				else if (a->default_transition_to && b->default_transition_to)
				{
					are_equal = regex_are_equal(cache,
						a->default_transition_to, b->default_transition_to);
				}
			}
			
			if (are_equal)
			{
				if (a->EOF_transition_to && !b->EOF_transition_to)
				{
					TODO;
				}
				else if (!a->EOF_transition_to && b->EOF_transition_to)
				{
					TODO;
				}
				else if (a->EOF_transition_to && b->EOF_transition_to)
				{
					are_equal = regex_are_equal(cache,
						a->EOF_transition_to, b->EOF_transition_to);
				}
			}
		}
		
		ele->are_equal = are_equal;
	}
	
	dpvb(ele->are_equal);
	
	EXIT;
	return are_equal;
}











