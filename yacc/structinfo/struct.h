
#include "node_kind.h"

struct structinfo_node
{
	struct string* name;
	
	enum structinfo_node_kind kind;
	
	struct string* grammar;
	
	unsigned refcount;
};

struct structinfo
{
	struct string* name;
	
	struct avl_tree_t* tree;
	
	unsigned refcount;
};

