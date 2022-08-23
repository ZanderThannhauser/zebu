
#include <parser/token/rbundle.h>

struct memory_arena;

struct rbundle regex_dfa_to_nfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* dfa);
