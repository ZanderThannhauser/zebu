
struct lex_state_ll
{
	struct avl_tree_t* cache;
	
	struct lex_state_link {
		struct lex_state* element;
		struct lex_state_link* next;
	}* head;
};

