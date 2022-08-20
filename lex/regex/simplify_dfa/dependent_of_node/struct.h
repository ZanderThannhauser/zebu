
#include "../pair/struct.h"

struct dependent_of_node
{
	struct pair pair;
	struct avl_tree_t* dependent_of;
};

