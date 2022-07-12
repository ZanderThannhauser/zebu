
#if 0
struct named_tokenset
{
	const char* name;
	struct tokenset* tokenset;
};

static struct named_tokenset* new_named_tokenset(const char* name, struct tokenset* tokenset)
{
	ENTER;
	
	struct named_tokenset* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->tokenset = tokenset;
	
	EXIT;
	return this;
}

static int compare_named_tokensets(const void* a, const void* b)
{
	const struct named_tokenset* A = a, *B = b;
	return strcmp(A->name, B->name);
}

static void free_named_tokenset(void* a)
{
	TODO;
}

static struct tokenset* lookup_tokenset(struct avl_tree_t* tree, const char* name)
{
	struct tokenset* retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(tree, &name);
	
	if (node)
	{
		struct named_tokenset* nt = node->item;
		retval = nt->tokenset;
	}
	else
	{
		retval = new_tokenset();
		
		avl_insert(tree, new_named_tokenset(name, retval));
	}
	
	EXIT;
	return retval;
}

#endif

