
#include <avl/tree_t.h>

struct regex;
struct stateset;
struct memory_arena;

struct regex* regex_nfa_to_dfa_helper(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regexset* states, // not yours to keep
	struct avl_tree_t* mappings);

