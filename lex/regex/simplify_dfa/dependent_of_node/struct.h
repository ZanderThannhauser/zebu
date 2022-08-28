
#include "../pair/struct.h"

struct regex_dependent_of_node
{
	struct regex_pair pair;
	
	struct avl_tree_t* dependent_of;
};

