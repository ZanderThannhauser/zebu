

typedef void (*avl_freeitem_t)(void *);

typedef int (*avl_compare_t)(const void *, const void *);

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

typedef struct avl_tree_t {
	avl_node_t *head;
	avl_node_t *tail;
	avl_node_t *top;
	
	avl_compare_t cmp;
	
	avl_freeitem_t freeitem;
} avl_tree_t;

#define NODE_DEPTH(n)  ((n) ? (n)->depth : 0)

#define R_DEPTH(n)     (NODE_DEPTH((n)->right))
#define L_DEPTH(n)     (NODE_DEPTH((n)->left))

avl_tree_t* avl_alloc_tree(
	avl_compare_t cmp,
	avl_freeitem_t freeitem);

void avl_clear_node(avl_node_t *newnode);


int avl_check_balance(avl_node_t *avlnode);

avl_node_t *avl_search(const avl_tree_t *avltree, const void *item);

avl_tree_t *avl_init_tree(
	avl_tree_t *rc,
	avl_compare_t cmp,
	avl_freeitem_t freeitem);

avl_node_t *avl_insert(avl_tree_t *avltree, void *item);

avl_node_t *avl_init_node(avl_node_t *newnode, void *item);

avl_node_t *avl_insert_node(avl_tree_t *avltree, avl_node_t *newnode);

avl_node_t *avl_insert_top(avl_tree_t *avltree, avl_node_t *newnode);

void avl_rebalance(avl_tree_t *avltree, avl_node_t *avlnode);

avl_node_t *avl_insert_after(avl_tree_t *avltree, avl_node_t *node, avl_node_t *newnode);

int avl_search_closest(const avl_tree_t *avltree, const void *item, avl_compare_t cmp, avl_node_t **avlnode);

void avl_free_tree(avl_tree_t *avltree);

void avl_clear_tree(avl_tree_t *avltree);

void avl_free_nodes(avl_tree_t *avltree);

avl_node_t *avl_insert_before(avl_tree_t *avltree, avl_node_t *node, avl_node_t *newnode);






















