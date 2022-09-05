
struct structinfo_node
{
	struct string* name;
	
	enum {
		sin_token,
		sin_grammar
	} kind;
	
	union {
		struct {
		
		} token;
		struct {
			struct string* name;
		} grammar;
	};
};

struct structinfo
{
	struct string* name;
	
	struct avl_tree_t* tree;
	
	unsigned refcount;
};

