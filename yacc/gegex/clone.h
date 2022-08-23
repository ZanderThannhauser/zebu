
#include <parser/grammar/gbundle.h>

struct gegex* gegex_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* in);

struct gbundle gegex_clone_nfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* start,
	struct gegex* end);
