
#include <avl/tree_t.h>

struct regex;
struct stateset;
struct memory_arena;

struct regex* regex_nfa_to_dfa_helper(
	struct regexset* states,
	struct avl_tree_t* mappings,
	struct memory_arena* arena);
