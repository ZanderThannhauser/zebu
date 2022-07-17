
#include <avl/avl.h>

struct regex;
struct stateset;
struct memory_arena;

struct regex* nfa_to_dfa_helper(
	struct stateset* states,
	struct avl_tree_t* mappings,
	struct memory_arena* arena);
