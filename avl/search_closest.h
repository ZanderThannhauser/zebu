
#include "tree_t.h"

/* Searches for a node with the key closest (or equal) to the given item.
 * If avlnode is not NULL, *avlnode will be set to the node found or NULL
 * if the tree is empty. Return values:
 *   -1  if the returned node is smaller
 *    0  if the returned node is equal or if the tree is empty
 *    1  if the returned node is greater
 * O(lg n) */
int avl_search_closest(const avl_tree_t *avltree, const void *item, avl_compare_t cmp, avl_node_t **avlnode);

