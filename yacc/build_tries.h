
struct avl_tree_t;
struct string;
struct gegex;
struct structinfo;

void build_tries(
	struct avl_tree_t* named_tries,
	struct string* name,
	struct gegex* start,
	struct structinfo* structinfo);
