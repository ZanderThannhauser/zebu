
#include <parser/grammar/gbundle.h>

struct gbundle gegex_from_subgrammar(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	char* grammar_name);
