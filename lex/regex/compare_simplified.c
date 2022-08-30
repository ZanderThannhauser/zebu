

#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <set/unsignedchar/compare.h>

#include "state/struct.h"

#include "compare_simplified.h"

struct node
{
	const struct regex* regex; // must be the first
	
	unsigned number;
};

static void insert_number(
	struct avl_tree_t* avl,
	const struct regex* regex,
	unsigned number)
{
	ENTER;
	
	struct node* new = malloc(sizeof(*new));
	
	new->regex = regex;
	new->number = number;
	
	avl_insert(avl, new);
	
	EXIT;
}

static int compare(const void* a, const void* b)
{
	const struct node* A = a, *B = b;
	
	if (A->regex > B->regex)
		return +1;
	else if (A->regex < B->regex)
		return -1;
	
	return 0;
}

int compare_simplified_regexes(
	const struct regex* a,
	const struct regex* b)
{
	ENTER;
	
	if (a == b)
	{
		dputs("a == b");
		EXIT;
		return 0;
	}
	
	struct avl_tree_t* a_numbers = avl_alloc_tree(compare, free);
	struct avl_tree_t* b_numbers = avl_alloc_tree(compare, free);
	
	unsigned next_number = 0;
	
	int helper(
		const struct regex* a,
		const struct regex* b)
	{
		int cmp = 0;
		ENTER;
		
		struct avl_node_t* is_a_numbered = avl_search(a_numbers, &a);
		struct avl_node_t* is_b_numbered = avl_search(b_numbers, &b);
		
		dpvb(is_a_numbered);
		dpvb(is_b_numbered);
		
		if (is_a_numbered && is_b_numbered)
		{
			unsigned a_number = ((struct node*) is_a_numbered->item)->number;
			unsigned b_number = ((struct node*) is_a_numbered->item)->number;
			
			dpv(a_number);
			dpv(b_number);
			
			if (a_number > b_number)
				cmp = +1;
			else if (a_number < b_number)
				cmp = -1;
		}
		else if (is_a_numbered)
		{
			// b is greater than a:
			cmp = -1;
		}
		else if (is_b_numbered)
		{
			// a is greater than b:
			cmp = +1;
		}
		else
		{
			insert_number(a_numbers, a, next_number);
			insert_number(b_numbers, b, next_number);
			
			next_number++;
			
			// compare acceptance?
			if (!!a->is_accepting > !!b->is_accepting)
				cmp = +1;
			else if (!!a->is_accepting < !!b->is_accepting)
				cmp = -1;
			
			unsigned a_i = 0, a_n = a->transitions.n,
				     b_i = 0, b_n = b->transitions.n;
			
			// compare transition values and destinations
			while (!cmp && a_i < a_n && b_i < b_n)
			{
				const struct regex_transition* const at = a->transitions.data[a_i];
				const struct regex_transition* const bt = b->transitions.data[b_i];
				
				dpvc(at->value);
				dpvc(bt->value);
				
				if (at->value < bt->value)
				{
					if (b->default_transition.to)
					{
						TODO;
					}
					else
						cmp = -1, a_i++;
				}
				else if (bt->value < at->value)
				{
					if (a->default_transition.to)
					{
						TODO;
					}
					else
						cmp = +1, b_i++;
				}
				else
					cmp = helper(at->to, bt->to), a_i++, b_i++;
			}
			
			while (!cmp && a_i < a_n && b->default_transition.to)
			{
				TODO;
			}
			
			while (!cmp && a->default_transition.to && b_i < b_n)
			{
				TODO;
			}
			
			if (!cmp)
			{
				if (a_i < a_n)
					cmp = +1;
				else if (b_i < b_n)
					cmp = -1;
			}
			
			// possibly compare default states
			if (!cmp)
			{
				const struct regex* const at = a->default_transition.to;
				const struct regex* const bt = b->default_transition.to;
				
				if (at)
					if (bt)
						cmp = 0
							?: compare_unsignedcharsets(
								a->default_transition.exceptions,
								b->default_transition.exceptions)
							?: helper(at, bt);
					else
						cmp = +1;
				else if (bt)
					cmp = -1;
			}
			
			// possibly compare EOF states
			if (!cmp)
			{
				const struct regex* const at = a->EOF_transition_to;
				const struct regex* const bt = b->EOF_transition_to;
				
				if (at)
					if (bt)
						cmp = helper(at, bt);
					else
						cmp = +1;
				else if (bt)
					cmp = -1;
			}
		}
		
		dpv(cmp);
		
		EXIT;
		return cmp;
	}
	
	int cmp = helper(a, b);
	
	dpv(cmp);
	
	avl_free_tree(a_numbers);
	avl_free_tree(b_numbers);
	
	EXIT;
	return cmp;
}





























