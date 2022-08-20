
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "avl.h"

static void avl_rebalance(avl_tree_t *, avl_node_t *);

unsigned int avl_count(const avl_tree_t *avltree) {
	return NODE_COUNT(avltree->top);
}

avl_node_t *avl_at(const avl_tree_t *avltree, unsigned int index) {
	avl_node_t *avlnode;
	unsigned int c;

	avlnode = avltree->top;

	while(avlnode) {
		c = L_COUNT(avlnode);

		if(index < c) {
			avlnode = avlnode->left;
		} else if(index > c) {
			avlnode = avlnode->right;
			index -= c+1;
		} else {
			return avlnode;
		}
	}
	return NULL;
}

unsigned int avl_index(const avl_node_t *avlnode) {
	avl_node_t *next;
	unsigned int c;

	c = L_COUNT(avlnode);

	while((next = avlnode->parent)) {
		if(avlnode == next->right)
			c += L_COUNT(next) + 1;
		avlnode = next;
	}

	return c;
}

avl_node_t *avl_search2(const avl_tree_t *avltree, const void *item, avl_compare_t cmp) {
	avl_node_t *node;
	return avl_search_closest(avltree, item, cmp, &node) ? NULL : node;
}

/*
 * avl_unlink_node:
 * Removes the given node.  Does not delete the item at that node.
 * The item of the node may be freed before calling avl_unlink_node.
 * (In other words, it is not referenced by this function.)
 */
void avl_unlink_node(avl_tree_t *avltree, avl_node_t *avlnode) {
	avl_node_t *parent;
	avl_node_t **superparent;
	avl_node_t *subst, *left, *right;
	avl_node_t *balnode;

	if(avlnode->prev)
		avlnode->prev->next = avlnode->next;
	else
		avltree->head = avlnode->next;

	if(avlnode->next)
		avlnode->next->prev = avlnode->prev;
	else
		avltree->tail = avlnode->prev;

	parent = avlnode->parent;

	superparent = parent
		? avlnode == parent->left ? &parent->left : &parent->right
		: &avltree->top;

	left = avlnode->left;
	right = avlnode->right;
	if(!left) {
		*superparent = right;
		if(right)
			right->parent = parent;
		balnode = parent;
	} else if(!right) {
		*superparent = left;
		left->parent = parent;
		balnode = parent;
	} else {
		subst = avlnode->prev;
		if(subst == left) {
			balnode = subst;
		} else {
			balnode = subst->parent;
			balnode->right = subst->left;
			if(balnode->right)
				balnode->right->parent = balnode;
			subst->left = left;
			left->parent = subst;
		}
		subst->right = right;
		subst->parent = parent;
		right->parent = subst;
		*superparent = subst;
	}

	avl_rebalance(avltree, balnode);
}

void *avl_delete_node(avl_tree_t *avltree, avl_node_t *avlnode) {
	void *item = NULL;
	if(avlnode) {
		item = avlnode->item;
		avl_unlink_node(avltree, avlnode);
		if(avltree->freeitem)
			avltree->freeitem(item);
		free(avlnode);
	}
	return item;
}

avl_node_t *avl_fixup_node(avl_tree_t *avltree, avl_node_t *newnode) {
	avl_node_t *oldnode = NULL, *node;

	if(!avltree || !newnode)
		return NULL;

	node = newnode->prev;
	if(node) {
		oldnode = node->next;
		node->next = newnode;
	} else {
		avltree->head = newnode;
	}

	node = newnode->next;
	if(node) {
		oldnode = node->prev;
		node->prev = newnode;
	} else {
		avltree->tail = newnode;
	}

	node = newnode->parent;
	if(node) {
		if(node->left == oldnode)
			node->left = newnode;
		else
			node->right = newnode;
	} else {
		oldnode = avltree->top;
		avltree->top = newnode;
	}

	return oldnode;
}

#endif
