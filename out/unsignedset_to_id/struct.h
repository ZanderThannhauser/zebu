
#include <stdbool.h>

struct unsignedset_to_id_node
{
	struct unsignedset* unsignedset;
	
	unsigned id;
};

struct unsignedset_to_id
{
	struct avl_tree_t* tree;
	
	unsigned next;
};
