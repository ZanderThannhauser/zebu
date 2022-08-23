
struct dynvector_node
{
	unsigned i, v;
};

struct dynvector
{
	struct avl_tree_t* list;
	const char* name;
	unsigned length;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

