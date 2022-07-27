
#include <stdbool.h>

struct regex;
struct avl_tree_t;

bool regex_are_equal(
	struct avl_tree_t* cache,
	const struct regex* a,
	const struct regex* b);
