
struct yacc_shared
{
	struct heap* todo;
	
	struct avl_tree_t* done;
	
	struct {
		struct avl_tree_t *sets; // named_tokensets
		struct avl_tree_t *dependant_of, *dependant_on; // named_strsets
	} firsts, lookaheads;
	
	// FILE* dotout_mk;
	
	struct avl_tree_t* grammar;
};
