
#include <parser/grammar/gbundle.h>

struct gegex* gegex_clone(
	struct gegex* in,
	struct memory_arena* arena);

struct gbundle gegex_clone_nfa(
	struct memory_arena* arena,
	struct gegex* start,
	struct gegex* end);
