
#include <stdbool.h>

struct avl_tree_t;
struct regex_pair;

bool regex_simplify_dfa_mark_as_unequal(
	struct avl_tree_t* connections,
	struct regex_pair* pair);