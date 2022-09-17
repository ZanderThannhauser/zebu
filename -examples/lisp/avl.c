
#include <errno.h>
#include <assert.h>
#include <stdlib.h>

#include "avl.h"

#define NODE_COUNT(n)  ((n) ? (n)->count : 0)
#define L_COUNT(n)     (NODE_COUNT((n)->left))
#define R_COUNT(n)     (NODE_COUNT((n)->right))
#define CALC_COUNT(n)  (L_COUNT(n) + R_COUNT(n) + 1)

#define CALC_DEPTH(n)  ((L_DEPTH(n)>R_DEPTH(n)?L_DEPTH(n):R_DEPTH(n)) + 1)


avl_tree_t* avl_alloc_tree(
	avl_compare_t cmp,
	avl_freeitem_t freeitem)
{
	return avl_init_tree(malloc(sizeof(avl_tree_t)), cmp, freeitem);
}

avl_node_t *avl_search(const avl_tree_t *avltree, const void *item)
{
	avl_node_t *node;
	return avl_search_closest(avltree, item, avltree->cmp, &node) ? NULL : node;
}

avl_tree_t *avl_init_tree(
	avl_tree_t *rc,
	avl_compare_t cmp,
	avl_freeitem_t freeitem)
{
	if (rc)
	{
		rc->head = NULL;
		rc->tail = NULL;
		rc->top = NULL;
		
		rc->cmp = cmp;
		
		rc->freeitem = freeitem;
	}
	return rc;
}

void avl_clear_node(avl_node_t *newnode)
{
	newnode->left = newnode->right = NULL;
	newnode->count = 1;
	newnode->depth = 1;
}

int avl_check_balance(avl_node_t *avlnode)
{
	int d;
	d = R_DEPTH(avlnode) - L_DEPTH(avlnode);
	return d < -1 ? -1 : d > 1 ? 1 : 0;
}


avl_node_t *avl_insert(avl_tree_t *avltree, void *item)
{
	avl_node_t *newnode;
	
	newnode = avl_init_node(malloc(sizeof(avl_node_t)), item);
	
	if (newnode)
	{
		if (avl_insert_node(avltree, newnode))
		{
			return newnode;
		}
		
		free(newnode);
		
		errno = EEXIST;
	}
	
	return NULL;
}

void avl_clear_tree(avl_tree_t *avltree)
{
	avltree->top = avltree->head = avltree->tail = NULL;
}

void avl_free_nodes(avl_tree_t *avltree)
{
	avl_node_t *node, *next;
	avl_freeitem_t freeitem;
	
	freeitem = avltree->freeitem;
	
	for (node = avltree->head; node; node = next)
	{
		next = node->next;
		
		if (freeitem)
		{
			freeitem(node->item);
		}
		
		free(node);
	}
	
	avl_clear_tree(avltree);
}

void avl_free_tree(avl_tree_t *avltree)
{
	if (avltree)
	{
		avl_free_nodes(avltree);
		
		free(avltree);
	}
}

avl_node_t *avl_init_node(avl_node_t *newnode, void *item)
{
	if (newnode) {
/*		avl_clear_node(newnode); */
		newnode->item = item;
	}
	return newnode;
}


avl_node_t *avl_insert_node(avl_tree_t *avltree, avl_node_t *newnode)
{
	avl_node_t *node;

	if (!avltree->top)
		return avl_insert_top(avltree, newnode);
	
	switch (avl_search_closest(avltree, newnode->item, avltree->cmp, &node))
	{
		case -1:
			return avl_insert_before(avltree, node, newnode);
		case 1:
			return avl_insert_after(avltree, node, newnode);
	}

	return NULL;
}

avl_node_t *avl_insert_top(avl_tree_t *avltree, avl_node_t *newnode)
{
	avl_clear_node(newnode);
	newnode->prev = newnode->next = newnode->parent = NULL;
	avltree->head = avltree->tail = avltree->top = newnode;
	return newnode;
}

avl_node_t *avl_insert_after(avl_tree_t *avltree, avl_node_t *node, avl_node_t *newnode)
{
	if (!node)
		return avltree->head
			? avl_insert_before(avltree, avltree->head, newnode)
			: avl_insert_top(avltree, newnode);

	if (node->right)
		return avl_insert_before(avltree, node->next, newnode);

	avl_clear_node(newnode);

	newnode->prev = node;
	newnode->parent = node;

	newnode->next = node->next;
	if (node->next)
		node->next->prev = newnode;
	else
		avltree->tail = newnode;
		
	node->next = newnode;

	node->right = newnode;
	
	avl_rebalance(avltree, node);
	
	return newnode;
}


void avl_rebalance(avl_tree_t *avltree, avl_node_t *avlnode)
{
	avl_node_t *child;
	avl_node_t *gchild;
	avl_node_t *parent;
	avl_node_t **superparent;

	parent = avlnode;

	while(avlnode) {
		parent = avlnode->parent;

		superparent = parent
			? avlnode == parent->left ? &parent->left : &parent->right
			: &avltree->top;

		switch(avl_check_balance(avlnode)) {
		case -1:
			child = avlnode->left;
			if(L_DEPTH(child) >= R_DEPTH(child)) {
				avlnode->left = child->right;
				if(avlnode->left)
					avlnode->left->parent = avlnode;
				child->right = avlnode;
				avlnode->parent = child;
				*superparent = child;
				child->parent = parent;
				avlnode->count = CALC_COUNT(avlnode);
				child->count = CALC_COUNT(child);
				avlnode->depth = CALC_DEPTH(avlnode);
				child->depth = CALC_DEPTH(child);
			} else {
				gchild = child->right;
				avlnode->left = gchild->right;
				if(avlnode->left)
					avlnode->left->parent = avlnode;
				child->right = gchild->left;
				if(child->right)
					child->right->parent = child;
				gchild->right = avlnode;
				if(gchild->right)
					gchild->right->parent = gchild;
				gchild->left = child;
				if(gchild->left)
					gchild->left->parent = gchild;
				*superparent = gchild;
				gchild->parent = parent;
				avlnode->count = CALC_COUNT(avlnode);
				child->count = CALC_COUNT(child);
				gchild->count = CALC_COUNT(gchild);
				avlnode->depth = CALC_DEPTH(avlnode);
				child->depth = CALC_DEPTH(child);
				gchild->depth = CALC_DEPTH(gchild);
			}
		break;
		case 1:
			child = avlnode->right;
			if(R_DEPTH(child) >= L_DEPTH(child)) {
				avlnode->right = child->left;
				if(avlnode->right)
					avlnode->right->parent = avlnode;
				child->left = avlnode;
				avlnode->parent = child;
				*superparent = child;
				child->parent = parent;
				avlnode->count = CALC_COUNT(avlnode);
				child->count = CALC_COUNT(child);
				avlnode->depth = CALC_DEPTH(avlnode);
				child->depth = CALC_DEPTH(child);
			} else {
				gchild = child->left;
				avlnode->right = gchild->left;
				if(avlnode->right)
					avlnode->right->parent = avlnode;
				child->left = gchild->right;
				if(child->left)
					child->left->parent = child;
				gchild->left = avlnode;
				if(gchild->left)
					gchild->left->parent = gchild;
				gchild->right = child;
				if(gchild->right)
					gchild->right->parent = gchild;
				*superparent = gchild;
				gchild->parent = parent;
				avlnode->count = CALC_COUNT(avlnode);
				child->count = CALC_COUNT(child);
				gchild->count = CALC_COUNT(gchild);
				avlnode->depth = CALC_DEPTH(avlnode);
				child->depth = CALC_DEPTH(child);
				gchild->depth = CALC_DEPTH(gchild);
			}
		break;
		default:
			avlnode->count = CALC_COUNT(avlnode);
			avlnode->depth = CALC_DEPTH(avlnode);
		}
		avlnode = parent;
	}
}

avl_node_t *avl_insert_before(avl_tree_t *avltree, avl_node_t *node, avl_node_t *newnode)
{
	if (!node)
		return avltree->tail
			? avl_insert_after(avltree, avltree->tail, newnode)
			: avl_insert_top(avltree, newnode);

	if (node->left)
		return avl_insert_after(avltree, node->prev, newnode);

	avl_clear_node(newnode);

	newnode->next = node;
	newnode->parent = node;

	newnode->prev = node->prev;
	if(node->prev)
		node->prev->next = newnode;
	else
		avltree->head = newnode;
	node->prev = newnode;

	node->left = newnode;
	avl_rebalance(avltree, node);
	return newnode;
}


int avl_search_closest(const avl_tree_t *avltree, const void *item, avl_compare_t cmp, avl_node_t **avlnode)
{
	avl_node_t *node;
	int c;
	
	if (!avlnode)
		avlnode = &node;
	
	node = avltree->top;
	
	if (!node)
		return *avlnode = NULL, 0;
	
	for (;;) {
		c = cmp(item, node->item);
		
		if(c < 0) {
			if(node->left)
				node = node->left;
			else
				return *avlnode = node, -1;
		} else if(c > 0) {
			if(node->right)
				node = node->right;
			else
				return *avlnode = node, 1;
		} else {
			return *avlnode = node, 0;
		}
	}
}



































