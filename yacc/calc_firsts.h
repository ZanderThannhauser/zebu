

struct avl_tree_t;
struct string;

struct firsts_node
{
	struct string* name;
	struct unsignedset* whitespace;
	struct unsignedset* tokens;
};


struct firsts_node* get_firsts(struct avl_tree_t* named_firsts, struct string* name);

struct avl_tree_t* calc_firsts(struct avl_tree_t* named_tries);
