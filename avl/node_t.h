
#ifndef AVL_NODE_T
#define AVL_NODE_T

typedef struct avl_node_t {
	struct avl_node_t *next;
	struct avl_node_t *prev;
	struct avl_node_t *parent;
	struct avl_node_t *left;
	struct avl_node_t *right;
	void *item;
	unsigned int count;
	unsigned char depth;
} avl_node_t;

#endif
