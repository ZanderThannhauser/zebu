
#include <parser/grammar/gbundle.h>

struct gbundle gegex_dfa_to_nfa(
	struct gegex* dfa,
	struct memory_arena* scratchpad);
