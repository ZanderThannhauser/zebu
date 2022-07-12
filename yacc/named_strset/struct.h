
#if 0
struct named_strset
{
	const char* name;
	struct strset* strset;
};

static struct named_strset* new_named_strset(const char* name, struct strset* strset)
{
	ENTER;
	
	dpvs(name);
	
	struct named_strset* new = smalloc(sizeof(*new));
	
	new->name = name;
	new->strset = strset;
	
	EXIT;
	return new;
}

static struct strset* lookup_strset(struct avl_tree_t* tree, const char* name)
{
	TODO;
}

static int compare_named_strsets(const void* a, const void* b)
{
	const struct named_strset* A = a, *B = b;
	return strcmp(A->name, B->name);
}

static void free_named_strset(void* a)
{
	struct named_strset* this = a;
	free_strset(this->strset);
	free(this);
}

#endif
