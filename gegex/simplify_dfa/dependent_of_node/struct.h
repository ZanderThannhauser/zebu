
#include "../pair/struct.h"

struct gegex_dependent_of_node
{
	struct gegex_pair pair;
	
	struct avl_tree_t* dependent_of;
};

