
#include <stdbool.h>

struct avl_tree_t;
struct lex_pair;

bool lex_simplify_dfa_mark_as_unequal(
	struct avl_tree_t* connections,
	struct lex_pair* pair);