
struct regex_ll
{
	struct avl_tree_t* cache;
	
	struct regex_link {
		struct regex* element;
		struct regex_link* next;
	}* head;
};

