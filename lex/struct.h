
#include <stdbool.h>

#include <avl/avl.h>

struct lex
{
	bool verbose;
	
	unsigned next_id;
	
	struct avl_tree_t nodes;
	
};
