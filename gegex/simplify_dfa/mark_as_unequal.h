
#include <stdbool.h>

struct avl_tree_t;
struct gegex_pair;

bool gegex_simplify_dfa_mark_as_unequal(
	struct avl_tree_t* connections,
	struct gegex_pair* pair);
