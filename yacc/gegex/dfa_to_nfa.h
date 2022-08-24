
#include <parser/grammar/gbundle.h>

struct gbundle gegex_dfa_to_nfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* dfa);
