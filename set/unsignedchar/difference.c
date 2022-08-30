
#include <debug.h>

#include "struct.h"
#include "difference.h"

struct unsignedcharset* unsignedcharset_difference(
	const struct unsignedcharset* a,
	const struct unsignedcharset* b)
{
	ENTER;
	
	struct avl_tree_t* tree = avl_alloc_tree(a->tree->cmp, free);
	
	unsigned n = 0;
	
	struct avl_node_t* a_node = a->tree->head;
	
	struct avl_node_t* b_node = b->tree->head;
	
	while (a_node && b_node)
	{
		unsigned char A = *((unsigned char*) a_node->item);
		unsigned char B = *((unsigned char*) b_node->item);
		
		if (A < B)
		{
			TODO;
			#if 0
			unsigned char* dup = smalloc(sizeof(*dup));
			
			*dup = A;
			
			avl_insert(tree, dup);
			
			a_node = a_node->next;
			n++;
			#endif
		}
		else if (A > B)
		{
			TODO;
			#if 0
			unsigned char* dup = smalloc(sizeof(*dup));
			
			*dup = B;
			
			avl_insert(tree, dup);
			
			b_node = b_node->next;
			n++;
			#endif
		}
		else
		{
			a_node = a_node->next;
			b_node = b_node->next;
		}
	}
	
	while (a_node)
	{
		unsigned char* dup = smalloc(sizeof(*dup));
		
		*dup = *((unsigned char*) a_node->item);
		
		avl_insert(tree, dup);
		
		a_node = a_node->next;
		
		n++;
	}
	
	while (b_node)
	{
		TODO;
		#if 0
		unsigned char* dup = smalloc(sizeof(*dup));
		
		*dup = *((unsigned char*) b_node->item);
		
		avl_insert(tree, dup);
		
		b_node = b_node->next;
		
		n++;
		#endif
	}
	
	struct unsignedcharset* this = smalloc(sizeof(*this));
	
	this->tree = tree;
	
	this->n = n;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

















