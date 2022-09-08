
#include "../pair/struct.h"

struct lex_dependent_of_node
{
	struct lex_pair pair;
	
	struct avl_tree_t* dependent_of;
};

